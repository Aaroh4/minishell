/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/24 13:29:51 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_heredocs(t_shell *sh)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (sh->cmd[i] != NULL)
	{
		j = 0;
		while (sh->cmd[i][j] != '\0')
		{
			if (sh->cmd[i][j] == '<' && sh->cmd[i][j + 1] == '<'
				&& sh->cmd[i][j + 2] != '<' && sh->cmd[i][j + 2] != '\0')
			{
				sh->hdocs[i]++;
				temp = ft_heredoc(sh->cmd[i], sh->hdocs[i]);
			}
			j++;
		}
		if (sh->hdocs[i] > 0)
			sh->cmd[i] = temp;
		i++;
	}
}

static void	trim_quote_alloc_hdoc_rdir(t_shell *sh)
{
	int		i;

	i = 0;
	i = 0;
	while (sh->cmd[i] != NULL)
	{
		sh->cmd[i] = trim_string(sh->cmd[i]);
		i++;
	}
	sh->cmd = remove_quotes_ex_export(sh->cmd);
	sh->hdocs = ft_calloc((i + 1), sizeof(int));
	sh->redirs = ft_calloc((i + 1), sizeof(int));
	if (sh->hdocs == NULL || sh->redirs == NULL)
		errexit("hdocs or redirs malloc error", NULL, NULL, sh);
	sh->hdocs[i] = -1;
	sh->redirs[i] = -1;
	get_heredocs(sh);
	get_redirects(sh);
}

static t_cmdn	*create_node(t_cmdn *current, t_shell *sh, int index)
{
	int		len;
	t_bool	first;

	len = 0;
	while (sh->cmdarr[len] != NULL)
		len++;
	sh->cmdarr[index] = trim_rdirspace(sh->cmdarr[index]);
	sh->cmd = ft_split_time_space(sh->cmdarr[index], ' ');
	print_char_array(sh->cmd);
	if (!(sh->cmd))
		errexit("error: ", "root malloc", NULL, sh);
	trim_quote_alloc_hdoc_rdir(sh);
	first = FALSE;
	if (index == 0)
		first = TRUE;
	if (index < len - 2)
	{
		current->left = init_cmd_node(COMMAND, sh, FALSE, first);
		current->right = init_cmd_node(PIPELINE, sh, FALSE, first);
		current = current->right;
	}
	else if (index == len - 2)
		current->left = init_cmd_node(COMMAND, sh, FALSE, first);
	else
		current->right = init_cmd_node(COMMAND, sh, TRUE, first);
	return (current);
}

void	create_pipes(t_shell *sh)
{
	int	cmdcount;

	cmdcount = 1;
	while (sh->cmdarr[cmdcount] != NULL)
		cmdcount++;
	if (cmdcount > 1)
	{
		if (pipe(sh->pfd[0]) == -1 || pipe(sh->pfd[1]) == -1)
			errexit("error :", "pipe initialization", NULL, sh);
	}
	sh->cmdcount = cmdcount;
	if (pipe(sh->efd) == -1)
		errexit("error :", "pipe initialization", NULL, sh);
}

void	parse_input(t_shell *sh)
{
	t_cmdn	*current;
	int		i;

	sh->root = init_cmd_node(PIPELINE, sh, FALSE, FALSE);
	if (!(sh->root))
		errexit("error: ", "root malloc", NULL, sh);
	sh->cmdarr = ft_split(sh->input, "|");
	if (!(sh->cmdarr))
		errexit("error: ", "cmdarr malloc", NULL, sh);
	free(sh->input);
	sh->input = NULL;
	current = sh->root;
	i = 0;
	while (sh->cmdarr[i] != NULL)
	{
		current = create_node(current, sh, i);
		i++;
	}
}
