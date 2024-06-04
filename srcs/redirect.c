/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:20:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/04 11:46:02 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ambiguous_redirect(int i, int j, t_shell *sh)
{
	char	*testparameter;

	testparameter = get_env_val_by_name(&sh->cmd[i][j + 1], sh);
	if (testparameter)
	{
		j = 0;
		while (testparameter[j] != '\0')
		{
			if (ft_isspace(testparameter[j]))
			{
				errprompt("Ambiguous redirect", NULL, NULL, sh);
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int	get_redirects(t_shell *sh)
{
	int	i;
	int	j;

	i = -1;
	while (sh->cmd[++i] != NULL)
	{
		j = -1;
		while (sh->cmd[i][++j] != '\0' && (sh->cmd[i][j] == '>'
				|| sh->cmd[i][j] == '<'))
		{
			if ((j == 0 || sh->cmd[i][j - 1] != '<') && sh->cmd[i][j] == '<' &&
					sh->cmd[i][j + 1] != '<')
			{
				if (check_ambiguous_redirect(i, j + 1, sh))
					return (1);
				sh->redirs[i] = 1;
			}
			else if ((j == 0 || sh->cmd[i][j - 1] != '>') &&
					sh->cmd[i][j] == '>' && sh->cmd[i][j + 1] != '>')
			{
				if (check_ambiguous_redirect(i, j + 1, sh))
					return (1);
				sh->redirs[i] = 2;
			}
			else if ((j == 0 || sh->cmd[i][j - 1] != '>') &&
					sh->cmd[i][j] == '>' && sh->cmd[i][j + 1] == '>' &&
					sh->cmd[i][j + 2] != '>')
			{
				if (check_ambiguous_redirect(i, j + 2, sh))
					return (1);
				sh->redirs[i] = 3;
			}
		}
	}
	return (0);
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
			redir_infile(sh, node, i, &inrdrs);
		else if (node->redirs[i] == 2)
		{
			if (redir_outfile_replace(sh, node, i, &outrdrs) == 1)
				return (1);
		}
		else if (node->redirs[i] == 3)
			if (redir_outfile_append(sh, node, i, &outrdrs) == 1)
				return (1);
	}
	if (sh->cmdcount > 1)
		redirects_more_command(sh, node, inrdrs, outrdrs);
	if (inrdrs > 0 || outrdrs > 0)
		omit_redirs_from_param(node);
	return (0);
}
