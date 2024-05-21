/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:20:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/21 18:12:46 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trim_space(char *c)
{
	char	*d;

	while (*c == ' ')
	{
		d = c;
		while (*d != '\0')
		{
			*d = *(d + 1);
			d++;
		}
		*d = '\0';
	}
}

static void	trim_outputs(char *c)
{
	if (*c == '>' && *(c + 1) != '\0')
	{
		if (*(c + 1) == '>' && *(c + 2) != '\0')
		{
			trim_space((c + 2));
			c++;
		}
		else
			trim_space(c + 1);
	}
}

static void	trim_inputs(char *c)
{
	if (*c == '<' && *(c + 1) != '\0')
	{
		if (*(c + 1) == '<' && *(c + 2) != '\0')
		{
			trim_space((c + 2));
			c++;
		}
		else
			trim_space((c + 1));
	}
}

// Gets the spaces away from between rediir symbols < > >>
// for easier manipulation later on.
char	*trim_rdirspace(char *cmd)
{
	char	*c;

	c = cmd;
	while (*c)
	{
		trim_outputs(c);
		trim_inputs(c);
		c++;
	}
	return (cmd);
}

void	get_redirects(t_shell *sh)
{
	int	i;
	int j;

	i = -1;
	while (sh->cmd[++i] != NULL)
	{
		j = -1;
		while (sh->cmd[i][++j] != '\0')
		{
			if ((j == 0 || sh->cmd[i][j - 1] != '<') && sh->cmd[i][j] == '<' &&
					sh->cmd[i][j + 1] != '<')
				sh->redirs[i] = 1;
			else if ((j == 0 || sh->cmd[i][j - 1] != '>') && 
					sh->cmd[i][j] == '>' && sh->cmd[i][j + 1] != '>')
				sh->redirs[i] = 2;
			else if ((j == 0 || sh->cmd[i][j - 1] != '>') && 
					sh->cmd[i][j] == '>' && sh->cmd[i][j + 1] == '>' && 
					sh->cmd[i][j + 2] != '>')
				sh->redirs[i] = 3;
		}
	}
}

/*
void 	print_array_redirs(t_cmdn *node)
{
	int	i;

	i = 0;
	while (node->cargs[i])
	{
		dprintf(2, "%d : %s\n", node->redirs[i], node->cargs[i]);
		i++;
	}
	return ;
}
*/
// Reconstruct cargs omitting redirs
static void	omit_redirs_from_param(t_cmdn *node)
{
	int		i;
	int		j;
	t_bool	flag;

	i = -1;
	j = 0;
	flag = FALSE;
	while (node->redirs[++i] != -1)
	{
		while (node->redirs[i] > 0 && flag == FALSE)
			i++;
		if (node->redirs[i] == 0)
		{
			node->cargs[j] = node->cargs[i];
			if (i != j++)
				node->cargs[i] = 0;
			flag = TRUE;
		}
		if (node->redirs[i] > 0 && flag == TRUE)
		{
			node->cargs[j] = 0;
			break ;
		}
	}
	node->cargs[i] = 0;
}

// 1 = input <
// 2 = output >
// 3 = output append >>
int	open_redirects(t_cmdn *node, t_shell *sh)
{
	int	i;
	int	inrdrs;
	int	outrdrs;
	int	in_fd;
	int	out_fd;

	i = 0;
	inrdrs = 0;
	outrdrs = 0;
	while (node->redirs[i] != -1)
	{
		if (node->redirs[i] == 1)
		{
			inrdrs++;
			in_fd = open(&node->cargs[i][1], O_RDONLY);
			if (in_fd == -1)
				errexit(&node->cargs[i][1], "No such file or directory", NULL, sh);
			else if (dup2(in_fd, STDIN_FILENO) == -1)
				errexit("error:", "dup2 stdin", NULL, sh);
			close(in_fd);
		}
		else if (node->redirs[i] == 2)
		{
			outrdrs++;
			out_fd = open(&node->cargs[i][1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (out_fd == -1)
			{
				printf("minishell: %s: Permission denied\n",
					&node->cargs[i][1]);
				return (1);
			}
			else if (dup2(out_fd, STDOUT_FILENO) == -1)
				 errexit("error:", "dup2 stdout replace", NULL, sh);
			close(out_fd);
		}
		else if (node->redirs[i] == 3)
		{
			outrdrs++;
			out_fd = open(&node->cargs[i][2], O_WRONLY | O_APPEND | O_CREAT,
					0644);
			if (out_fd == -1)
			{
				printf("minishell: %s: Permission denied\n",
					&node->cargs[i][2]);
				return (1);
			}
			else if (dup2(out_fd, STDOUT_FILENO) == -1)
				errexit("error:", "dup2 stdout append", NULL, sh);
			close(out_fd);
		}
		i++;
	}

	// Strategy: call pipe between each command, close previous pipe
	if (sh->cmdcount > 1)
	{
		if (inrdrs == 0 && sh->cmdcount > 1 && node->first == FALSE)
		{
			if (dup2(sh->pfd[0], STDIN_FILENO) == -1)
				errexit("error:", "dup2 stdin", NULL, sh);
		}
		else 
			close(sh->pfd[0]);
		if (outrdrs == 0 && sh->cmdcount > 1 && node->last == FALSE)
		{
			if (dup2(sh->pfd[1], STDOUT_FILENO) == -1)
				errexit("error:", "dup2 stdout", NULL, sh);
		}
		else
			close(sh->pfd[1]);
	}
	if (inrdrs > 0 || outrdrs > 0)
		omit_redirs_from_param(node);
	return (0);
}
