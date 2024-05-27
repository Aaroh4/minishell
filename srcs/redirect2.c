/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:26:43 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/27 22:21:29 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_redir(t_shell *sh, t_cmdn *node, int i, int *inrdrs)
{
	int	in_fd;

	(*inrdrs)++;
	in_fd = open(&node->cargs[i][1], O_RDONLY);
	if (in_fd == -1)
		errexit(&node->cargs[i][1],
			": No such file or directory", NULL, sh);
	else if (dup2(in_fd, STDIN_FILENO) == -1)
		errexit("error:", "dup2 stdin", NULL, sh);
	close(in_fd);
}

int	second_redir(t_shell *sh, t_cmdn *node, int i, int *outrdrs)
{
	int	out_fd;

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

int	third_redir(t_shell *sh, t_cmdn *node, int i, int *outrdrs)
{
	int	out_fd;

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
