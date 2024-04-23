/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/22 18:58:34 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_cmdn	*init_cmd_node(t_ntype type, t_shell *sh, t_bool last)
{
	t_cmdn	*new_cmdn;

	new_cmdn = malloc(sizeof(t_cmdn));
	if (new_cmdn != NULL)
	{
		new_cmdn->ntype = type;
		new_cmdn->left = NULL;
		new_cmdn->right = NULL;
		new_cmdn->cargs = NULL;
		if (type == COMMAND)
		{
			new_cmdn->cargs = sh->cmd;
			new_cmdn->hdocs = sh->hdocs;
		}
		else
		{
			new_cmdn->cargs = NULL;
			new_cmdn->hdocs = NULL;
		}
		new_cmdn->last = last;
		sh->cmd = NULL;
		sh->hdocs = NULL;
	}
	else
		errexit("error: ", "cmd node malloc", sh, 1);
	return (new_cmdn);
}

char	**ft_remove_quotes(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '\"')
			{
				while (cmd[i][j] != '\0')
				{
					cmd[i][j] = cmd[i][j + 1];
					j++;
				}
				j = 0;
			}
			j++;
		}
		i++;
	}
	return (cmd);
}

static t_cmdn	*create_node(t_cmdn *current, t_shell *sh, int i, int len)
{
	int		j;
	char	*temp;

	sh->cmd = ft_split_time_space(sh->cmdarr[i], ' ');
	if (!(sh->cmd))
		errexit("error: ", "root malloc", sh, 1);
	j = 0;
	while (sh->cmd[j] != NULL)
	{
		sh->cmd[j] = ft_strtrim(sh->cmd[j], " ");
		j++;
	}
	sh->cmd = ft_remove_quotes(sh->cmd);
	sh->hdocs = ft_calloc((j + 1), sizeof(int));
	if (sh->hdocs == NULL)
	{
		perror("hdocs malloc error");
		exit(1);
	}
	sh->hdocs[j] = -1;
	j = 0;
	while (sh->cmd[j] != NULL)
	{
		if (sh->cmd[j][0] == '<' && sh->cmd[j][1] == '<'
			&& sh->cmd[j][2] != '<')
		{
			sh->hdocs[j]++;
			temp = ft_heredoc(sh->cmd[j], sh->hdocs[j]);
		}
		j++;
	}
	if (sh->hdocs[j] > 0)
	{
		sh->cmd[j] = temp;
	}
	if (i < len - 2)
	{
		current->left = init_cmd_node(COMMAND, sh, FALSE);
		current->right = init_cmd_node(PIPELINE, sh, FALSE);
		current = current->right;
	}
	else if (i == len - 2)
		current->left = init_cmd_node(COMMAND, sh, FALSE);
	else
		current->right = init_cmd_node(COMMAND, sh, TRUE);
	return (current);
}

void	parse_input(t_shell *sh)
{
	t_cmdn	*current;
	int		i;
	int		len;

	sh->root = init_cmd_node(PIPELINE, sh, FALSE);
	if (!(sh->root))
		errexit("error: ", "root malloc", sh, 1);
	sh->cmdarr = ft_split(sh->input, "|");
	current = sh->root;
	len = 0;
	while (sh->cmdarr[len] != NULL) // Slated for removal to create_node
		len++;
	i = 0;
	while (sh->cmdarr[i] != NULL)
	{
		current = create_node(current, sh, i, len);
		i++;
	}
}

void	print_cmdn(t_cmdn *node)
{
	int	i;

	if (node == NULL)
		return ;
	print_cmdn(node->left);
	i = 0;
	if (node->ntype == COMMAND)
		ft_putendl_fd("COMMAND:", 2);
	if (node->ntype == PIPELINE)
		ft_putendl_fd("PIPELINE:", 2);
	while (node->cargs && node->cargs[i] != 0)
	{
		if (i != 0)
			ft_putchar_fd('\t', 2);
		ft_putendl_fd(node->cargs[i], 2);
		i++;
	}
	ft_putnbr_fd(node->last, 2);
	ft_putchar_fd('\n', 2);
	print_cmdn(node->right);
}
