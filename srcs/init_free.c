/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:06:04 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/10 13:41:14 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	init_shell_struct(t_shell *sh)
{
	sh->ms_envp = NULL;
	sh->input = NULL;
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
	sh->redirs = NULL;
	// Should this be -1 to check for actual update?
	sh->status = 0;
}

void	free_args(char **args)
{
	int	i;

	if (!args || !*args)
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
	if (node == NULL)
		return ;
	free_cmdn(node->left);
	dprintf(2, "free_cmdn starting\n");
	dprintf(2, "type: %s\n", node->ntype);
	if (node->cargs)
	{
		free_args(node->cargs);
		dprintf(2, "- free cargs\n");
	}
	if (node->hdocs)
	{
		free(node->hdocs);
		dprintf(2, "- free hdocs\n");
	}
	if (node->redirs)
	{
		free(node->redirs);
		dprintf(2, "- free redirs\n");
	}
	node->hdocs = NULL;
	node->redirs = NULL;
	node->cargs = NULL;
	free_cmdn(node->right);
	free(node);
	node = NULL;
}

void	free_new_prompt(t_shell *sh)
{
	dprintf(2, "free parent starting\n");
	free_cmdn(sh->root);
	dprintf(2, "- free root\n");
	free_args(sh->cmdarr);
	dprintf(2, "- free cmdarr\n");
	close(sh->pfd[0]);
	close(sh->pfd[1]);
	close(sh->efd[0]);
	close(sh->efd[1]);
	free_args(sh->cmd);
	dprintf(2, "- free cmd\n");
	free(sh->hdocs);
	dprintf(2, "- free hdocs\n");
	free(sh->redirs);
	sh->input = NULL;
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
	sh->redirs = NULL;
}

void	free_fork(t_shell *sh)
{
	dprintf(2, "free child starting\n");
	free_cmdn(sh->root);
	dprintf(2, "- free root\n");
	free_args(sh->cmdarr);
	dprintf(2, "- free cmdarr\n");
	close(sh->pfd[0]);
	// close(sh->pfd[1]);
	close(sh->efd[0]);
	// close(sh->efd[1]);
	// free_args(sh->cmd);
	dprintf(2, "- free cmd\n");
	// free(sh->hdocs);
	dprintf(2, "- free hdocs\n");
	// free(sh->redirs);
	// dprintf(2, "free redirs\n");
	sh->input = NULL;
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
	sh->redirs = NULL;
}
