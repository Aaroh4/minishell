/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:26:43 by ahamalai          #+#    #+#             */
/*   Updated: 2024/06/04 11:44:58 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	check_ambiguous_redirect(int i, int j, t_cmdn *node, t_shell *sh)
{
	dprintf(2, "Got here.");
	while (node->cargs[i][j] != '\0')
	{
		if (!ft_isalnum(node->cargs[i][j]))
		{
			errexit("Ambiguous redirect", NULL, NULL, sh);
			j++;
		}
	}
}
*/

void	redir_infile(t_shell *sh, t_cmdn *node, int i, int *inrdrs)
{
	int	in_fd;

	//check_ambiguous_redirect(i, 1, node, sh);
	(*inrdrs)++;
	in_fd = open(&node->cargs[i][1], O_RDONLY);
	if (in_fd == -1)
		errexit(&node->cargs[i][1],
			": No such file or directory", NULL, sh);
	else if (dup2(in_fd, STDIN_FILENO) == -1)
		errexit("error:", "dup2 stdin", NULL, sh);
	close(in_fd);
}

int	redir_outfile_replace(t_shell *sh, t_cmdn *node, int i, int *outrdrs)
{
	int	out_fd;

	//check_ambiguous_redirect(i, 1, node, sh);
	(*outrdrs)++;
	out_fd = open(&node->cargs[i][1], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (out_fd == -1)
	{
		printf("minishell: %s: Permission denied\n",
			&node->cargs[i][1]);
		return (1);
	}
	else if (dup2(out_fd, STDOUT_FILENO) == -1)
		errexit("error:", "dup2 stdout replace", NULL, sh);
	close(out_fd);
	return (0);
}

int	redir_outfile_append(t_shell *sh, t_cmdn *node, int i, int *outrdrs)
{
	int	out_fd;

	//check_ambiguous_redirect(i, 2, node, sh);
	(*outrdrs)++;
	out_fd = open(&node->cargs[i][2], O_WRONLY | O_APPEND | O_CREAT,
			0644);
	if (out_fd == -1)
	{
		printf("minishell: %s: Permission denied\n",
			&node->cargs[i][2]);
		return (1);
	}
	else if (dup2(out_fd, STDOUT_FILENO) == -1)
		errexit("error:", "dup2 stdout append", NULL, sh);
	close(out_fd);
	return (0);
}

void	redirects_more_command(t_shell *sh, t_cmdn *node,
			int inrdrs, int outrdrs)
{
	if (inrdrs == 0 && sh->cmdcount > 1 && node->first == FALSE)
	{
		if (dup2(sh->pfd[0][0], STDIN_FILENO) == -1)
			errexit("error:", "dup2 stdin", NULL, sh);
	}
	else
		close(sh->pfd[0][0]);
	if (outrdrs == 0 && sh->cmdcount > 1 && node->last == FALSE)
	{
		if (dup2(sh->pfd[1][1], STDOUT_FILENO) == -1)
			errexit("error:", "dup2 stdout", NULL, sh);
	}
	else
		close(sh->pfd[0][1]);
}
