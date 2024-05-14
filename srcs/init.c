/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 08:34:10 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/14 08:40:13 by mburakow         ###   ########.fr       */
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

// Should here be more validation for cmd and hdocs?
// Here they are just passed to the command from sh, then the same pointers
// are used again for the next cmd.
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
		new_cmdn->hdocs = NULL;
		if (type == COMMAND)
		{
			new_cmdn->cargs = sh->cmd;
			new_cmdn->hdocs = sh->hdocs;
			new_cmdn->redirs = sh->redirs;
		}
		new_cmdn->last = last;
		sh->cmd = NULL;
		sh->hdocs = NULL;
	}
	else
		errexit("error: ", "cmd node malloc", NULL, sh);
	return (new_cmdn);
}