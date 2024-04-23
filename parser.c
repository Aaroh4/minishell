/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/23 15:20:57 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// Should here be more validation for cmd and hdocs?
static t_cmdn	*init_cmd_node(t_ntype type, t_shell *sh, t_bool last)
{
	t_cmdn	*new_cmdn;

	new_cmdn = malloc(sizeof(t_cmdn));
	if (new_cmdn != NULL)
	{
		new_cmdn->ntype = type;
		new_cmdn->left = NULL;
		new_cmdn->right = NULL;
		new_cmdn->cargs = NULL;
		new_cmdn->hdocs = NULL;
		if (type == COMMAND)
		{
			new_cmdn->cargs = sh->cmd;
			new_cmdn->hdocs = sh->hdocs;
		}
		new_cmdn->last = last;
		sh->cmd = NULL;
		sh->hdocs = NULL;
	}
	else
		errexit("error: ", "cmd node malloc", sh, 1);
	return (new_cmdn);
}

static void	trim_quote_alloc_hdoc(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->cmd[i] != NULL)
	{
		sh->cmd[i] = ft_strtrim(sh->cmd[i], " ");
		i++;
	}
	sh->cmd = ft_remove_quotes(sh->cmd);
	sh->hdocs = ft_calloc((i + 1), sizeof(int));
	if (sh->hdocs == NULL)
	{
		perror("hdocs malloc error");
		exit(1);
	}
	sh->hdocs[i] = -1;
}

static void	get_heredocs(t_shell *sh)
{
	int		i;
	char	*temp;

	i = 0;
	while (sh->cmd[i] != NULL)
	{
		if (sh->cmd[i][0] == '<' && sh->cmd[i][1] == '<'
			&& sh->cmd[i][2] != '<')
		{
			sh->hdocs[i]++;
			temp = ft_heredoc(sh->cmd[i], sh->hdocs[i]);
		}
		i++;
	}
	if (sh->hdocs[i] > 0)
	{
		sh->cmd[i] = temp;
	}
}

static t_cmdn	*create_node(t_cmdn *current, t_shell *sh, int index)
{
	int	len;

	len = 0;
	while (sh->cmdarr[len] != NULL)
		len++;
	sh->cmd = ft_split_time_space(sh->cmdarr[index], ' ');
	if (!(sh->cmd))
		errexit("error: ", "root malloc", sh, 1);
	trim_quote_alloc_hdoc(sh);
	get_heredocs(sh);
	if (index < len - 2)
	{
		current->left = init_cmd_node(COMMAND, sh, FALSE);
		current->right = init_cmd_node(PIPELINE, sh, FALSE);
		current = current->right;
	}
	else if (index == len - 2)
		current->left = init_cmd_node(COMMAND, sh, FALSE);
	else
		current->right = init_cmd_node(COMMAND, sh, TRUE);
	return (current);
}

void	parse_input(t_shell *sh)
{
	t_cmdn	*current;
	int		i;

	sh->root = init_cmd_node(PIPELINE, sh, FALSE);
	if (!(sh->root))
		errexit("error: ", "root malloc", sh, 1);
	sh->cmdarr = ft_split(sh->input, "|");
	current = sh->root;
	i = 0;
	while (sh->cmdarr[i] != NULL)
	{
		current = create_node(current, sh, i);
		i++;
	}
}
