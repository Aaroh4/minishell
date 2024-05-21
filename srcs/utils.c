/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/21 15:39:51 by mburakow         ###   ########.fr       */
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
	return(NULL);
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
	char	**cmdi;
	char	*cur;
	int		i;

	cmdi = cmd;
	while (*cmdi != NULL)
	{
		cur = *cmdi;
		// dprintf(2, "cur is: %s\n", cur);
		while (*cur != '\0')
		{
			if (*cur == '\"')
			{
				i = 0;
				while (cur[i + 1] != '\0')
				{
					cur[i] = cur[i + 1];
					i++;
				}
				cur[i] = '\0';
			}
			cur++;
		}
		cmdi++;
	}
	return (cmd);
}

// At the moment accounts only for space characters,
//	are other characters necessary?
char	*trim_string(char *str)
{
	int		i;
	char	*end;
	char 	*curs;

	i = 0;
	if (!str || str[0] == '\0' || str[0] == 0)
		return (str);
	while ((unsigned char)str[i] == 32)
		i++;
	curs = &str[i];
	i = 0;
	if (*curs == '\0')
	{
		str[i] = *curs;
		return (str);
	}
	while (*curs != '\0')
	{
		str[i++] = *curs;
		curs++;
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && (unsigned char)*end == 32)
		end--;
	end[1] = '\0';
	return (str);
}

void	print_array(char **arr)
{
	int i;
	i = 0;
	while (arr[i])
		dprintf(2, "%s\n", arr[i++]);

}
