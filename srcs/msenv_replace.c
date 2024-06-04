/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/04 15:06:28 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msenv.h"

static void	init_env_struct(t_env_tdata *envd)
{
	envd->start = NULL;
	envd->end = NULL;
	envd->env_val = NULL;
	envd->temp = NULL;
	envd->total_len = 0;
}

static void	determine_env(t_shell *sh, t_env_tdata *envd, int i)
{
	if (*(envd->start + 1) == 63)
	{
		envd->env_val = ft_itoa(sh->status);
		return ;
	}
	if (ft_isdigit(*(envd->start + 1)))
	{
		envd->env_val = ft_strdup("");
		envd->end = ft_strdup(envd->start + 2);
		return ;
	}
	while (sh->ms_envp[i] != NULL)
	{
		if (!ft_strncmp(sh->ms_envp[i], envd->start + 1,
				ft_strcpos(sh->ms_envp[i], 61)))
		{
			envd->env_val = ft_strdup(ft_strchr(sh->ms_envp[i], 61) + 1);
			envd->end = envd->start + ft_strcpos(sh->ms_envp[i], 61) + 1;
			break ;
		}
		i++;
	}
	if (envd->env_val == NULL)
		envd->env_val = ft_strdup("");
}

char	*alloc_new_arr(char *input, t_shell *sh, t_env_tdata *envd)
{
	char	*new_arr;
	int		i;

	i = 0;
	determine_env(sh, envd, i);
	envd->total_len = ft_strlen(input) - ft_strlen(envd->start)
		+ ft_strlen(envd->env_val) + ft_strlen(envd->end);
	new_arr = (char *)malloc((envd->total_len + 1) * sizeof(char));
	if (new_arr == NULL)
		errexit("ms_envp: ", "malloc 3 error", NULL, sh);
	envd->temp = input;
	return (new_arr);
}

void	write_new_arr(char *new_arr, t_env_tdata *envd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strcpos(envd->temp, 36))
	{
		new_arr[i] = envd->temp[i];
		i++;
	}
	while (envd->env_val[j] != '\0')
	{
		new_arr[i] = envd->env_val[j];
		i++;
		j++;
	}
	envd->start = new_arr + i;
	while (*envd->end != '\0')
	{
		new_arr[i] = *envd->end;
		i++;
		envd->end++;
	}
	new_arr[i] = '\0';
}

char	*replace_envp_tags(char *input, t_shell *sh)
{
	t_env_tdata	envd;
	char		*new_arr;

	init_env_struct(&envd);
	envd.start = ft_strchr(input, 36);
	if (envd.start != NULL && !ft_isalnum(*(envd.start + 1)))
		return (input);
	while (envd.start != NULL)
	{
		envd.end = move_to_env_end(envd.start + 1);
		new_arr = alloc_new_arr(input, sh, &envd);
		write_new_arr(new_arr, &envd);
		free(envd.env_val);
		free(input);
		input = new_arr;
		envd.start = ft_strchr((envd.start + 1), 36);
	}
	return (input);
}
