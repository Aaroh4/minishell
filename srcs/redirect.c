/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:20:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/27 10:35:27 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_redirects(t_shell *sh)
{
	int	i;
	int	j;

	i = -1;
	while (sh->cmd[++i] != NULL)
	{
		j = -1;
		while (sh->cmd[i][++j] != '\0')
		{
			if ((j == 0 || sh->cmd[i][j - 1] != '<') && sh->cmd[i][j] == '<'
				&& sh->cmd[i][j + 1] != '<')
				sh->redirs[i] = 1;
			else if ((j == 0 || sh->cmd[i][j - 1] != '>') &&
					sh->cmd[i][j] == '>' && sh->cmd[i][j + 1] != '>')
				sh->redirs[i] = 2;
			else if ((j == 0 || sh->cmd[i][j - 1] != '>') &&
					sh->cmd[i][j] == '>' && sh->cmd[i][j + 1] == '>' &&
					sh->cmd[i][j + 2] != '>')
				sh->redirs[i] = 3;
		}
	}
}

static void	omit_redirs_from_param(t_cmdn *node)
{
	int		i;
	int		j;
	t_bool	flag;

	i = -1;
	j = 0;
	flag = FALSE;
	while (node->redirs[++i] != -1)
	{
		while (node->redirs[i] > 0 && flag == FALSE)
			i++;
		if (node->redirs[i] == 0)
		{
			node->cargs[j] = node->cargs[i];
			if (i != j++)
				node->cargs[i] = 0;
			flag = TRUE;
		}
		if (node->redirs[i] > 0 && flag == TRUE)
		{
			node->cargs[j] = 0;
			break ;
		}
	}
	node->cargs[i] = 0;
}

int	open_redirects(t_cmdn *node, t_shell *sh)
{
	int	i;
	int	inrdrs;
	int	outrdrs;

	i = -1;
	inrdrs = 0;
	outrdrs = 0;
	while (node->redirs[++i] != -1)
	{
		if (node->redirs[i] == 1)
			first_redir(sh, node, i, &inrdrs);
		else if (node->redirs[i] == 2)
		{
			if (second_redir(sh, node, i, &outrdrs) == 1)
				return (1);
		}
		else if (node->redirs[i] == 3)
			if (third_redir(sh, node, i, &outrdrs) == 1)
				return (1);
	}
	if (sh->cmdcount > 1)
		redirects_more_command(sh, node, inrdrs, outrdrs);
	if (inrdrs > 0 || outrdrs > 0)
		omit_redirs_from_param(node);
	return (0);
}
