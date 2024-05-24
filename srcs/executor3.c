/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:47:02 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/24 13:30:20 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_temp(t_shell *sh, char *str)
{
	int		i;
	char	**temp;

	i = 0;
	while (sh->ms_envp[i] != 0)
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (sh->ms_envp[i] != 0)
	{
		temp[i] = sh->ms_envp[i];
		i++;
	}
	free(sh->ms_envp);
	temp[i] = ft_subbstr(str, 0, ft_strlen(str) - 1);
	temp[i + 1] = NULL;
	return (temp);
}

char	*getting_multiple_param(t_shell *sh, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (sh->ms_envp[i] != 0)
	{
		j = 0;
		while (sh->ms_envp[i][j] == str[j] && sh->ms_envp[i][j] != '=')
			j++;
		if (str[j] == '=')
			break ;
		i++;
	}
	if (str[j] == '=')
	{
		free (sh->ms_envp[i]);
		sh->ms_envp[i] = ft_subbstr(str, 0, ft_strlen(str));
	}
	else
		sh->ms_envp = make_temp(sh, str);
	free(str);
	str = get_next_line(sh->efd[0]);
	return (str);
}

void	env_modify_loop(t_shell *sh, int a, char *cwd, char *str)
{
	char	*temp;

	str = get_next_line(sh->efd[0]);
	if (a == 2)
		str = ft_strjoin("OLDPWD=", cwd);
	if (str == NULL && a != 2)
		return ;
	while (str != NULL)
	{
		if (a == 1)
		{
			if (chdir(str) == -1)
			{
				printf("cd: %s: No such file or directory\n", str);
				free(str);
				return ;
			}
			temp = str;
			str = ft_strjoin("PWD=", temp);
			free(temp);
			modify_env(sh, 2, cwd);
		}
		str = getting_multiple_param(sh, str);
	}
}

void	modify_env(t_shell *sh, int a, char *cwd)
{
	char	*str;

	close(sh->efd[1]);
	str = NULL;
	if (sh->cmdcount == 1)
		env_modify_loop(sh, a, cwd, str);
	close(sh->efd[0]);
}
