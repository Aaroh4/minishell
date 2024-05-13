/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/13 15:53:52 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

 void	*db_malloc(size_t size)
 {
	return (malloc(size));
 }

char	*get_exec_path(char **path, char *cmd)
{
	char	*slashpath;
	char	*execpath;

	execpath = NULL;
	slashpath = NULL;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
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

void	print_cmdn(t_cmdn *node)
{
	int	i;

	if (node == NULL)
		return ;
	print_cmdn(node->left);
	i = 0;
	if (node->ntype == COMMAND)
		ft_putendl_fd("COMMAND:", 2);
	if (node->ntype == PIPELINE)
		ft_putendl_fd("PIPELINE:", 2);
	while (node->cargs && node->cargs[i] != 0)
	{
		if (i != 0)
			ft_putchar_fd('\t', 2);
		ft_putendl_fd(node->cargs[i], 2);
		i++;
	}
	ft_putnbr_fd(node->last, 2);
	ft_putchar_fd('\n', 2);
	print_cmdn(node->right);
}

char	**ft_remove_quotes(char **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '\"')
			{
				while (cmd[i][j] != '\0')
				{
					cmd[i][j] = cmd[i][j + 1];
					j++;
				}
				j = 0;
			}
			else
				j++;
		}
	}
	return (cmd);
}

// At the moment accounts only for space characters,
//	are other characters necessary?
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