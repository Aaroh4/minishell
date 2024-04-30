/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:15:11 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/30 12:51:02 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	cd_builtin(char *cwd, char **str)
{
	char	cwd2[1024];
	char	*realcwd;

	// NEEDS A WHOLE NEW REWRITE BECAUSE THIS IS DOGSHIT!!
	if (getcwd(cwd2, sizeof(cwd2)) == NULL)
		perror("getcwd error");
	if (str[1] == NULL)
	{
		chdir(cwd);
	}
	else if (!ft_strncmp(str[1], ".", 2))
		return (1);
	else if (!ft_strncmp(str[1], "..", 3))
	{
		chdir(ft_substr(cwd2, 0, ft_strlen(cwd2) - ft_strlen(ft_strrchr(cwd2,
						'/'))));
	}
	else
	{
		realcwd = ft_strjoin(cwd2, "/");
		chdir(ft_strjoin(realcwd, str[1]));
	}
	return (1);
	// NEEDS A WHOLE NEW REWRITE BECAUSE THIS IS DOGSHIT!!
}

int	pwd_builtin(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd error");
	return (1);
}

void	exit_builtin(t_shell *sh)
{
	free_new_prompt(sh);
	free_args(sh->ms_envp);
	write(1, "exit\n", 5);
	exit(0);
}

int	echo_builtin(char **arg)
{
	int	i;

	i = 1;
	if (ft_strncmp(arg[i], "-n", 3))
	{
		while (arg[i] != NULL)
		{
			printf("%s", arg[i++]);
			if (arg[i] != NULL)
				printf("%s", " ");
		}
		printf("\n");
	}
	else
	{
		i++;
		while (arg[i] != NULL)
		{
			printf("%s", arg[i++]);
			if (arg[i] != NULL)
				printf("%s", " ");
		}
	}
	return (1);
}

int	export_builtin(t_cmdn *node, t_shell *sh)
{
	int	i;

	i = 0;
	while ((node->cargs[1][i] >= 'a' && node->cargs[1][i] <= 'z')
		|| (node->cargs[1][i] >= 'A' && node->cargs[1][i] <= 'Z'))
		i++;
	if (node->cargs[1][i] == '=')
		ft_putstr_fd(node->cargs[1], sh->efd[1]);
	return (1);
}

int	env_builtin(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->ms_envp[i])
	{
		printf("%s\n", sh->ms_envp[i]);
		i++;
	}
	return (1);
}
