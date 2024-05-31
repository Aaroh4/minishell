/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:06:04 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/31 12:49:29 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}

void	free_cmdn(t_cmdn *node)
{
	static int r = 0;
	
	if (node == NULL)
		return ;
	if (node->left)
		free_cmdn(node->left);
	if (node->right)
		free_cmdn(node->right);
	r++;
	if (node->cargs)
	{
		free_args(node->cargs);
		dprintf(2, "[%d][%d] Freed cargs\n", r, node->ntype);
	}
	free(node->hdocs);
	dprintf(2, "[%d][%d] Freed hdocs\n", r, node->ntype);
	free(node->redirs);
	dprintf(2, "[%d][%d] Freed redirs\n", r, node->ntype);
	node->cargs = NULL;
	node->hdocs = NULL;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	free(node);
	node = NULL;
}

void	free_new_prompt(t_shell *sh)
{
	free_cmdn(sh->root);
	if (sh->cmdcount > 1)
		close_ext_pipes(sh);
	free_args(sh->cmdarr);
	free_args(sh->cmd);
	// free(sh->hdocs);
	// free(sh->redirs);
	sh->input = NULL;
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
	sh->redirs = NULL;
}

void	close_ext_pipes(t_shell *sh)
{
	close(sh->pfd[0][0]);
	close(sh->pfd[0][1]);
	close(sh->pfd[1][0]);
	close(sh->pfd[1][1]);
	close(sh->efd[0]);
	close(sh->efd[1]);
}

void	free_child(t_shell *sh)
{
	free_cmdn(sh->root);
	free_args(sh->cmdarr);
	free_args(sh->ms_envp);
	if (sh->cmdcount > 1)
		close_ext_pipes(sh);
	free_args(sh->cmd);
	free(sh->hdocs);
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->ms_envp = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
}
