/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/23 13:51:21 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*db_malloc(size_t size)
{
	return (malloc(size));
}

static char	*get_exec_path_env(char **path, char *cmd)
{
	char	*slashpath;
	char	*execpath;

	while (*path)
	{
		slashpath = ft_strjoin(*path, "/");
		execpath = ft_strjoin(slashpath, cmd);
		free(slashpath);
		slashpath = NULL;
		if (access(execpath, X_OK) != -1)
			return (execpath);
		free(execpath);
		execpath = NULL;
		path++;
	}
	return (NULL);
}

char	*get_exec_path(char **path, char *cmd, t_shell *sh)
{
	char	*slashpath;
	char	*execpath;

	execpath = NULL;
	slashpath = NULL;
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, X_OK) != -1)
			return (cmd);
		else
			return (NULL);
	}
	else if (cmd[0] == '~')
	{
		slashpath = get_env_val_by_name("HOME", sh);
		execpath = ft_strjoin(slashpath, &cmd[1]);
		free(slashpath);
		slashpath = NULL;
		return (execpath);
	}
	else
		return (get_exec_path_env(path, cmd));
	return (NULL);
}

int	wait_for(t_intvec *commands)
{
	int	status;
	int	nc;

	nc = 0;

	while (commands->array[nc + 1])
	{
		waitpid(commands->array[nc], &status, 0);
		nc++;
	}
	waitpid(commands->array[nc], &status, 0);
	return (WEXITSTATUS(status));
}
