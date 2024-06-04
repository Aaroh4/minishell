/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/04 10:16:26 by ahamalai         ###   ########.fr       */
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
			j = skip_quotes(sh->cmd[i], j);
			if (sh->cmd[i][j + 1] == '\0' || sh->cmd[i][j + 2] == '\0')
				break ;
			if (sh->cmd[i][j] == '<' && sh->cmd[i][j + 1] == '<'
				&& sh->cmd[i][j + 2] != '<' && sh->cmd[i][j + 2] != '\0')
			{
				sh->hdocs[i]++;
				temp = ft_heredoc(sh->cmd[i], sh->hdocs[i], sh);
			}
			j++;
		}
		if (sh->hdocs[i] > 0)
			sh->cmd[i] = temp;
		i++;
	}
}

static int	trim_quote_alloc_hdoc_rdir(t_shell *sh)
{
	int		i;

	i = 0;
	while (sh->cmd[i] != NULL)
	{
		sh->cmd[i] = trim_string(sh->cmd[i]);
		i++;
	}
	sh->hdocs = ft_calloc((i + 1), sizeof(int));
	sh->redirs = ft_calloc((i + 1), sizeof(int));
	if (sh->hdocs == NULL || sh->redirs == NULL)
		errexit("hdocs or redirs malloc error", NULL, NULL, sh);
	sh->hdocs[i] = -1;
	sh->redirs[i] = -1;
	get_heredocs(sh);
	if (get_redirects(sh))
		return (1);
	i = 0;
	while (sh->cmd[i] != NULL)
	{
		if (sh->hdocs[i] == 0)
			sh->cmd[i] = remove_quote_level(sh->cmd[i], sh);
		i++;
	}
	return (0);
}

static t_cmdn	*create_node(t_cmdn *current, t_shell *sh, int index, int len)
{
	t_bool	first;

	while (sh->cmdarr[len] != NULL)
		len++;
	sh->cmdarr[index] = trim_rdirspace(sh->cmdarr[index]);
	sh->cmd = split_pipes(sh->cmdarr[index], " ");
	if (!(sh->cmd))
		errexit("error: ", "root malloc", NULL, sh);
	if (trim_quote_alloc_hdoc_rdir(sh))
		return (NULL);
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

int	parse_input(t_shell *sh)
{
	t_cmdn	*current;
	int		i;
	int		len;

	len = 0;
	sh->root = init_cmd_node(PIPELINE, sh, FALSE, FALSE);
	if (!(sh->root))
		errexit("error: ", "root malloc", NULL, sh);
	sh->cmdarr = split_pipes(sh->input, "|");
	if (!(sh->cmdarr))
		errexit("error: ", "cmdarr malloc", NULL, sh);
	free(sh->input);
	sh->input = NULL;
	current = sh->root;
	i = 0;
	while (sh->cmdarr[i] != NULL)
	{
		current = create_node(current, sh, i, len);
		if (current == NULL)
			return (1);
		i++;
	}
	return (0);
}
