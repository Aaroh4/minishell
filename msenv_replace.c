/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/29 12:33:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include "./includes/msenv.h"

// Still missing check for heredoc and single/double quotes
char	*move_ucase(char *start)
{
	char	*ptr;

	ptr = start;
	while ((*ptr >= 65 && *ptr <= 90) || *ptr == 95 || *ptr == 63)
		ptr++;
	return (ptr);
}

// If question mark, ignore caps after, else check from ms_envp for the value
static void	determine_env(t_shell *sh, t_env_tdata *envd)
{
	int	i;

	i = 0;
	if (*(envd->start + 1) == 63)
	{
		envd->env_val = ft_itoa(sh->status);
		return ;
	}
	while (sh->ms_envp[i] != NULL)
	{
		if (!ft_strncmp(sh->ms_envp[i], envd->start + 1,
				ft_strcpos(sh->ms_envp[i], 61)))
		{
			envd->env_val = ft_strchr(sh->ms_envp[i], 61) + 1;
			envd->end = envd->start + ft_strcpos(sh->ms_envp[i], 61) + 1;
			break ;
		}
		i++;
	}
}

char	*alloc_new_arr(char *input, t_shell *sh, t_env_tdata *envd)
{
	char	*new_arr;

	determine_env(sh, envd);
	envd->total_len = ft_strlen(input) - ft_strlen(envd->start)
		+ ft_strlen(envd->env_val) + ft_strlen(envd->end);
	new_arr = (char *)malloc((envd->total_len + 1) * sizeof(char));
	if (new_arr == NULL)
	{
		perror("ms_envp malloc 3 error");
		exit(1);
	}
	envd->temp = input;
	return (new_arr);
}

void	write_new_arr(char *new_arr, t_env_tdata *envd)
{
	int	i;

	i = 0;
	while (envd->temp != envd->start)
	{
		new_arr[i] = *envd->temp;
		envd->temp++;
		i++;
	}
	while (*envd->env_val != '\0')
	{
		new_arr[i] = *envd->env_val;
		i++;
		envd->env_val++;
	}
	envd->start = new_arr + i;
	while (*envd->end != '\0')
	{
		new_arr[i] = *envd->end;
		i++;
		envd->end++;
	}
	new_arr[ft_strlen(new_arr)] = '\0';
}

// Some characters or combinations seem to prevent env substitution,
// when directly after the env. This has not yet been researched/implemented.
// Should we include hdoc checks here or before at populate_env_vars?
// INIT ENVDATA STRUCT MORON!!!
char	*replace_envp(char *input, t_shell *sh)
{
	t_env_tdata	envd;
	char		*new_arr;

	envd.start = ft_strchr(input, 36);
	while (envd.start != NULL)
	{
		envd.end = move_ucase(envd.start + 1);
		envd.env_val = "";
		new_arr = alloc_new_arr(input, sh, &envd);
		write_new_arr(new_arr, &envd);
		free(input);
		input = new_arr;
		envd.start = ft_strchr((envd.start + 1), 36);
	}
	return (input);
}
