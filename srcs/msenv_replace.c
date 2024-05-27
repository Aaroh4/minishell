/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv_replace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/27 15:23:00 by mburakow         ###   ########.fr       */
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

void print_env_struct(t_env_tdata *envd)
{
	static int i = 0;

	i++;
	dprintf(2, "### logno: %d ###\n", i);
	dprintf(2, "envd->start = %s\n", envd->start);
	dprintf(2, "envd->end =  %s\n", envd->end);
	dprintf(2, "envd->env_val =  %s\n", envd->env_val);
	dprintf(2, "envd->temp =  %s\n", envd->temp);
	dprintf(2, "envd->total_len = %d\n", envd->total_len);
}

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
		errexit("ms_envp: ", "malloc 3 error", NULL, sh);
	envd->temp = input;
	return (new_arr);
}

// IT'S HERE SOMEWHERE!!!!
void	write_new_arr(char *new_arr, t_env_tdata *envd)
{
	int	i;

	i = 0;
	dprintf(2, "NEW ARR START!\n");
	print_env_struct(envd);
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
	new_arr[i] = '\0';
	print_env_struct(envd);
	dprintf(2, "NEW ARR: %s\n", new_arr);
}

char	*replace_envp_tags(char *input, t_shell *sh)
{
	t_env_tdata	envd;
	char		*new_arr;

	init_env_struct(&envd);
	envd.start = ft_strchr(input, 36);
	print_env_struct(&envd);
	while (envd.start != NULL)
	{
		envd.end = move_ucase(envd.start + 1);
		envd.env_val = "";
		print_env_struct(&envd);
		new_arr = alloc_new_arr(input, sh, &envd);
		write_new_arr(new_arr, &envd);
		free(input);
		input = new_arr;
		print_env_struct(&envd);
		envd.start = ft_strchr((envd.start + 1), 36);
		print_env_struct(&envd);
	}
	return (input);
}
