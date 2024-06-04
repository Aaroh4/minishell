/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 08:34:10 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/04 10:14:30 by ahamalai         ###   ########.fr       */
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
	sh->status = 0;
}

void	init_nulls(t_shell *sh)
{
	sh->cmd = NULL;
	sh->hdocs = NULL;
	sh->redirs = NULL;
}

t_cmdn	*init_cmd_node(t_ntype type, t_shell *sh, t_bool last, t_bool first)
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
		new_cmdn->redirs = NULL;
		if (type == COMMAND)
		{
			new_cmdn->cargs = sh->cmd;
			new_cmdn->hdocs = sh->hdocs;
			new_cmdn->redirs = sh->redirs;
		}
		new_cmdn->last = last;
		new_cmdn->first = first;
		init_nulls(sh);
	}
	else
		errexit("error: ", "cmd node malloc", NULL, sh);
	return (new_cmdn);
}
