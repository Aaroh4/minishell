/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/23 11:35:49 by mburakow         ###   ########.fr       */
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

int	wait_for(t_intvec *commands)
{
	int	status;
	int	nc;

	nc = 0;
	while (commands->array[nc])
	{
		// ft_putstr_fd("Waited for :", 2);
		// ft_putnbr_fd(waitpid(commands->array[nc], &status, 0), 2);
		// ft_putchar_fd('\n', 2);
		waitpid(commands->array[nc], &status, 0);
		nc++;
	}
	return (WEXITSTATUS(status));
}

/* At the moment accounts only for space characters,
	are other characters necessary?
char	*trim_string(char *str)
{
	char	*end;

	while ((unsigned char)*str == 32)
		str++;
	if (*str == '\0')
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (unsigned char)*end == 32)
		end--;
	end[1] = '\0';
	return (str);
}
*/