/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:06:04 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/14 16:04:39 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void my_free(void* p)
{
	dprintf(2, "Freeing pointer %p\n", p);
	free(p);
}
*/

// Upper pointer must be freed even if only value is NULL
void	free_args(char **args)
{
	int	i;

	if (!args) // || !*args)
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
	{
		free_args(node->cargs);
		// dprintf(2, "Freed cmd cargs.\n");
	}
	free(node->hdocs);
	// dprintf(2, "Freed cmd hdocs.\n");
	/* DONT FREE THIS BULLSHIT!!!
	if (node->redirs)
	{
		my_free(node->redirs);
		dprintf(2, "Freed cmd redirs.\n");
	}
	*/
	node->cargs = NULL;
	node->hdocs = NULL;
	node->redirs = NULL;
	node->left = NULL;
	node->right = NULL;
	// dprintf(2, "Freeing cmd node.\n");
	free(node);
	// dprintf(2, "Freed node.\n");
	node = NULL;
}

void	free_new_prompt(t_shell *sh)
{
	free_cmdn(sh->root);
	// dprintf(2, "Freed root cmd structure.\n");
	free_args(sh->cmdarr);
	// dprintf(2, "Freed cmdarr.\n");
	close(sh->pfd[0]);
	close(sh->pfd[1]);
	close(sh->efd[0]);
	close(sh->efd[1]);
	close(sh->sfd[0]);
	close(sh->sfd[1]);
	free_args(sh->cmd);
	// dprintf(2, "Freed cmd.\n");
	free(sh->hdocs);
	// dprintf(2, "Freed hdocs.\n");
	free(sh->redirs);
	// dprintf(2, "Freed redirs.\n");
	sh->input = NULL;
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
	//sh->redirs = NULL;
}

void	close_all_pipes(t_shell *sh)
{
	close(sh->pfd[0]);
	close(sh->pfd[1]);
	close(sh->efd[0]);
	close(sh->efd[1]);
	close(sh->sfd[0]);
	close(sh->sfd[1]);
}

void	free_child(t_shell *sh)
{
	free_cmdn(sh->root);
	// dprintf(2, "Freed root cmd structure.\n");
	free_args(sh->cmdarr);
	// dprintf(2, "Freed cmdarr.\n");
	free_args(sh->ms_envp);
	// dprintf(2, "Freed ms_envp.\n");
	close(sh->pfd[0]);
	// close(sh->pfd[1]);
	close(sh->efd[0]);
	// close(sh->efd[1]);
	free_args(sh->cmd);
	// dprintf(2, "Freed cmd.\n");
	// free(sh->input);
	// dprintf(2, "Freed input.\n");
	free(sh->hdocs);
	// dprintf(2, "Freed hdocs.\n");
	// free(sh->redirs);
	// dprintf(2, "Freed redirs.\n");
	// sh->input = NULL;
	sh->root = NULL;
	sh->cmdarr = NULL;
	sh->ms_envp = NULL;
	sh->cmd = NULL;
	sh->hdocs = NULL;
	// c sh->redirs = NULL;
	// dprintf(2, "Freeing child process complete.\n");
}
