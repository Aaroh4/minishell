/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv_modify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:42:56 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/14 18:32:51 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Doesn't check for validity of name (should exist) or value
void	modify_env_internal(char *name, char *value, t_shell *sh)
{
	int		i;
	int 	eqpos;
	char	*env_name;
	char	*new;
	char 	*temp;

	i = 0;
	eqpos = 0;
	while (sh->ms_envp[i] != NULL)
	{
		eqpos = ft_strcpos(sh->ms_envp[i], 61);
		env_name = ft_substr(sh->ms_envp[i], 0, eqpos);
		if (!ft_strncmp(name, env_name, eqpos))
		{
			temp = ft_strjoin(name, "=");
			new = ft_strjoin(temp, value);
			free(temp);
			temp = sh->ms_envp[i];
			free(temp);
			sh->ms_envp[i] = new;
			free(env_name);
			break;
		}
		i++;
	}
	return ;
}

char	*get_env_val_by_name(char *name, t_shell *sh)
{
	int		i;
	int		eqpos;
	char	*env_name;
	// char	*value;

	i = 0;
	eqpos = 0;
	while (sh->ms_envp[i] != NULL)
	{
		eqpos = ft_strcpos(sh->ms_envp[i], 61);
		env_name = ft_substr(sh->ms_envp[i], 0, eqpos);
		if (!ft_strncmp(name, env_name, eqpos))
		{
			// value = ft_strdup(sh->ms_envp[i], eqpos);
			return(&sh->ms_envp[i][eqpos + 1]);
		}
		i++;
	}
	return (NULL);
}