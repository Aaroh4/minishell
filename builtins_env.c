/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:34:19 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/25 15:48:22 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// Problem: command might not be at cargs[0]
void	export_builtin(t_cmdn *node, t_shell *sh)
{
	if (node->cargs[1] == NULL)
	{
		print_env(sh->ms_envp);
		return ;
	}
	else if (ft_strchr(node->cargs[1], '='))
	{
		// Check if the variable already exists
		if (find_env_var(node->cargs[1], sh->ms_envp) == -1)
		{
			sh->ms_envp = add_env_var(node->cargs[1], sh->ms_envp);
			return ;
		}
		else
		{
			sh->ms_envp = change_env_var(node->cargs[1], sh->ms_envp);
			return ;
		}
	}
	else // Error bad syntax
		return ;
}

void	unset_builtin(t_cmdn *node, t_shell *sh)
{
	return (1);
}

void	env_builtin(t_cmdn *node, t_shell *sh)
{
	return (1);
}
