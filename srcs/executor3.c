/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:47:02 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/30 11:26:50 by ahamalai         ###   ########.fr       */
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
	temp[i] = ft_substr(str, 0, ft_strlen(str) - 1);
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
		sh->ms_envp[i] = ft_substr(str, 0, ft_strlen(str) - 1);
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

void	make_child(t_cmdn *node, t_shell *sh, t_intvec *commands, char *cwd)
{
	int		pid;

	pid = 0;
	signal(SIGQUIT, ft_handler_child2);
	signal(SIGINT, ft_handler_child);
	pid = fork();
	if (pid == -1)
	{
		sh->status = wait_for(commands);
		free_intvec(commands);
		errexit("Error:", "fork failure", NULL, sh);
	}
	else if (pid == 0)
	{
		if (pipe(sh->hfd) == -1)
			errexit("error :", "pipe initialization", NULL, sh);
		free_intvec(commands);
		exec_cmd(node, sh, cwd);
	}
	else
	{
		check_builtin(node, sh, cwd);
		if (commands != NULL)
			add_to_intvec(commands, pid, sh);
	}
}
