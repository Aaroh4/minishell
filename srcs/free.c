/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:06:04 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/21 13:20:10 by ahamalai         ###   ########.fr       */
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
	if (node == NULL)
		return ;
	if (node->left)
		free_cmdn(node->left);
	if (node->right)
		free_cmdn(node->right);
	if (node->cargs)
		free_args(node->cargs);
	free(node->hdocs);
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
		close_all_pipes(sh);
	free_args(sh->cmdarr);
	free_args(sh->cmd);
	free(sh->hdocs);
	free(sh->redirs);
	sh->input = NULL;
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
}

void	close_all_pipes(t_shell *sh)
{
	close(sh->pfd[0]);
	close(sh->pfd[1]);
	//close(sh->efd[0]);
	//close(sh->efd[1]);
}

void	free_child(t_shell *sh)
{
	free_cmdn(sh->root);
	free_args(sh->cmdarr);
	free_args(sh->ms_envp);
	if (sh->cmdcount > 1)
		close_all_pipes(sh);
	free_args(sh->cmd);
	free(sh->hdocs);
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->ms_envp = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
}
