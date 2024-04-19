/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:15:11 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/17 13:08:31 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

#include <stdio.h>
#include <unistd.h>

void	cd_builtin(char *cwd, char **str)
{
	char	cwd2[1024];
	char	*realcwd;

	if (getcwd(cwd2, sizeof(cwd2)) == NULL)
		perror("getcwd error");
	if (str[1] == NULL)
	{
		chdir(cwd);
	}
	else if (!ft_strncmp(str[1], ".", 2))
		return ;
	else if (!ft_strncmp(str[1], "..", 3))
	{
		chdir(ft_substr(cwd2, 0, ft_strlen(cwd2)
				- ft_strlen(ft_strrchr(cwd2, '/'))));
	}
	else
	{
		realcwd = ft_strjoin(cwd2, "/");
		chdir(ft_strjoin(realcwd, str[1]));
	}
}

void	pwd_builtin(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd error");
}

void	exit_builtin(void)
{
	write(1, "exit\n", 5);
	exit (0);
}

void	echo_builtin(char **arg)
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
}
