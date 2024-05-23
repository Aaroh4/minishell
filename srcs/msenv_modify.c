/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv_modify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:42:56 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/23 13:58:55 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increase_shell_level(t_shell *sh)
{
	char	*val;
	int		shlvl;

	val = get_env_val_by_name("SHLVL", sh);
	shlvl = ft_atoi(val) + 1;
	val = ft_itoa(shlvl);
	modify_env_internal("SHLVL", val, sh);
	free(val);
}

// Doesn't check for validity of name (should exist) or value
void	modify_env_internal(char *name, char *value, t_shell *sh)
{
	int		i;
	int		eqpos;
	char	*env_name;
	char	*new;
	char	*temp;

	i = -1;
	eqpos = 0;
	while (sh->ms_envp[++i] != NULL)
	{
		eqpos = ft_strcpos(sh->ms_envp[i], 61);
		env_name = ft_substr(sh->ms_envp[i], 0, eqpos);
		if (!ft_strncmp(name, env_name, eqpos))
		{
			temp = ft_strjoin(name, "=");
			new = ft_strjoin(temp, value);
			free(temp);
			free(sh->ms_envp[i]);
			sh->ms_envp[i] = new;
			free(env_name);
			break ;
		}
		free(env_name);
	}
	return ;
}

char	*get_env_val_by_name(char *name, t_shell *sh)
{
	int		i;
	int		eqpos;
	char	*env_name;

	i = 0;
	eqpos = 0;
	env_name = NULL;
	while (sh->ms_envp[i] != NULL)
	{
		eqpos = ft_strcpos(sh->ms_envp[i], 61);
		env_name = ft_substr(sh->ms_envp[i], 0, eqpos);
		if (!ft_strncmp(name, env_name, eqpos))
		{
			free(env_name);
			env_name = NULL;
			return (&sh->ms_envp[i][eqpos + 1]);
		}
		free(env_name);
		env_name = NULL;
		i++;
	}
	return (NULL);
}
