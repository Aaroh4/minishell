/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:20:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/07 14:38:38 by ahamalai         ###   ########.fr       */
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

// Rewrite this:
void	get_redirects(t_shell *sh)
{
	int	i;
	int	j;

	i = -1;
	while (sh->cmd[++i] != NULL)
	{
		j = -1;
		while (sh->cmd[i][++j] != '\0')
		{
			if (sh->cmd[i][j - 1] != '<' && sh->cmd[i][j] == '<' && sh->cmd[i][j
				+ 1] != '<')
				sh->redirs[i] = 1;
			else if (sh->cmd[i][j - 1] != '>' && sh->cmd[i][j] == '>'
				&& sh->cmd[i][j + 1] != '>')
				sh->redirs[i] = 2;
			else if (sh->cmd[i][j - 1] != '>' && sh->cmd[i][j] == '>'
				&& sh->cmd[i][j + 1] == '>' && sh->cmd[i][j + 2] != '>')
				sh->redirs[i] = 3;
		}
	}
}

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

// Errors do not correspond to bash errors yet
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
			// dprintf(2, "Redir: %d type: %d filename: %s\n", i, node->redirs[i],
			//	&node->cargs[i][1]);
			in_fd = open(&node->cargs[i][1], O_RDONLY);
			if (in_fd == -1)
			{
				printf("minishell: %s: No such file or directory\n",
					&node->cargs[i][1]);
				return (1);
			}
			else if (dup2(in_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 fail infile");
				return (1);
			}
			close(in_fd);
		}
		else if (node->redirs[i] == 2)
		{
			outrdrs++;
			// dprintf(2, "Redir: %d type: %d filename: %s\n", i, node->redirs[i],
			//	&node->cargs[i][1]);
			out_fd = open(&node->cargs[i][1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (out_fd == -1)
			{
				printf("minishell: %s: Permission denied\n",
					&node->cargs[i][1]);
				return (1);
			}
			else if (dup2(out_fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 fail outfile");
				return (1);
			}
			close(out_fd);
		}
		else if (node->redirs[i] == 3)
		{
			outrdrs++;
			// dprintf(2, "Redir: %d type: %d filename: %s\n", i, node->redirs[i],
			//	&node->cargs[i][2]);
			out_fd = open(&node->cargs[i][2], O_WRONLY | O_APPEND | O_CREAT,
					0644);
			if (out_fd == -1)
			{
				printf("minishell: %s: Permission denied\n",
					&node->cargs[i][2]);
				return (1);
			}
			else if (dup2(out_fd, STDOUT_FILENO) == -1)
			{
				errexit("error:", "dup2 stdin", sh, 127);
			}
			close(out_fd);
		}
		i++;
	}
	if (inrdrs == 0)
	{
		if (dup2(sh->pfd[0], STDIN_FILENO) == -1)
			errexit("error:", "dup2 stdin", sh, 127);
	}
	close(sh->pfd[0]);
	close(sh->efd[0]);
	if (outrdrs == 0 && node->last == FALSE)
	{
		if (dup2(sh->pfd[1], STDOUT_FILENO) == -1)
			errexit("error:", "dup2 stdout", sh, 127);
	}
	i = 0;
	if (inrdrs > 0 || outrdrs > 0)
	{
		omit_redirs_from_param(node);
	}
	return (0);
}
