/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:29:16 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/23 13:46:42 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_remove_hdocs(int i, t_cmdn *node)
{
	int	j;
	int	k;
	int	*temp;

	j = 0;
	while (node->hdocs[j] != -1)
		j++;
	temp = malloc(sizeof(int *) * j);
	j = 0;
	k = 0;
	while (node->hdocs[j] != -1)
	{
		if (i != j)
			temp[k] = node->hdocs[j];
		else
			k--;
		j++;
		k++;
	}
	temp[k] = -1;
	return (temp);
}

void	handle_heredocs(t_cmdn *node, t_shell *sh)
{
	int	i;

	i = 0;
	while (node->hdocs[i] != -1)
		i++;
	i--;
	while (node->hdocs[i] == 0 && i > 0)
		i--;
	if (node->hdocs[i] > 0)
	{
		node->cargs[i] = replace_envp(node->cargs[i], sh);
		ft_putstr_fd(node->cargs[i], sh->hfd[1]);
	}
	i = 0;
	while (node->cargs[i] != 0)
	{
		if (node->hdocs[i] > 0)
		{
			node->cargs = remove_from_array(node->cargs, i, node);
			i = 0;
		}
		else
			i++;
	}
}

int	check_hdocs(t_cmdn *node)
{
	int	i;

	i = 0;
	while (node->hdocs[i] != -1)
	{
		if (node->hdocs[i] > 0)
			return (1);
		i++;
	}
	return (0);
}

char	**remove_from_array(char **str, int i, t_cmdn *node)
{
	char	**temp;
	int		j;
	int		k;

	j = 0;
	while (str[j] != 0)
		j++;
	temp = malloc(sizeof(char *) * j);
	j = 0;
	k = 0;
	while (str[j] != 0)
	{
		if (i != j)
			temp[k] = str[j];
		else
			k--;
		j++;
		k++;
	}
	temp[k] = NULL;
	node->hdocs = ft_remove_hdocs(i, node);
	return (temp);
}

int	exec_builtin(t_cmdn *node, t_shell *sh, char *cwd)
{
	if (node->cargs[0] && !ft_strncmp(node->cargs[0], "exit", 5))
		return (1);
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "echo", 5))
		return (echo_builtin(node->cargs));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "cd", 3))
		return (cd_builtin(node, sh, cwd));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "pwd", 4))
		return (pwd_builtin(sh));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "export", 7))
		return (export_builtin(node, sh));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "unset", 6))
		return (unset_builtin(node, sh));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "env", 4))
		return (env_builtin(sh, FALSE));
	close (sh->efd[0]);
	close (sh->efd[1]);
	return (0);
}
