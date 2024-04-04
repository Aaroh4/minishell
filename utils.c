/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/04 16:57:22 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*get_exec_path(char **path, char *cmd)
{
	char	*slashpath;
	char	*execpath;

	execpath = NULL;
	slashpath = NULL;
	while (*path)
	{
		slashpath = ft_strjoin(*path, "/");
		execpath = ft_strjoin(slashpath, cmd);
		if (access(execpath, X_OK) != -1)
			return (execpath);
		else
		{
			if (execpath)
				free(execpath);
			execpath = NULL;
		}
		path++;
	}
	if (!path)
		return (cmd);
	return (NULL);
}

void	free_args(char **args)
{
	int	i;

	if (!args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}