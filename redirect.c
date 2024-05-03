/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:20:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/03 23:23:21 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void trim_space(char *c)
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
	// printf("%s\n", cmd);
	return (cmd);
}

void	get_redirects(t_shell *sh)
{
	// char	*c;
	int		i;
	int		j;
	int		in_fd;
	int		out_fd;

	i = 0; 
	while (sh->cmd[i] != NULL)
	{
		j = 0;
		while (sh->cmd[i][j] != '\0')
		{
			if (sh->cmd[i][j - 1] != '<' && 
				sh->cmd[i][j] == '<' && 
				sh->cmd[i][j + 1] != '<')
			{
				sh->redirs[i] = 1;
				// Try to open the file and redirect STDIN
				// from the rightmost file
 			}
			else if (sh->cmd[i][j - 1] != '>' && 
				sh->cmd[i][j] == '>' && 
				sh->cmd[i][j + 1] != '>')
			{
				sh->redirs[i] = 2;
				// Try to create/open the file in replace mode and redirect STDOUT
				// to the rightmost file
			}
			else if (sh->cmd[i][j + 1] != '>' && 
				sh->cmd[i][j] == '>' && 
				sh->cmd[i][j + 1] == '>' &&
				sh->cmd[i][j + 1] != '>')
			{
				sh->redirs[i] = 3;
				// Try to create/open the file in append mode and redirect STDOUT
				// to the rightmost file
			}
			j++;
		}
		i++;
	}
	i = 0;
	/*printf("Redirs:");
	while (sh->redirs[i] != -1)
	{
		printf(" %d", sh->redirs[i]);
		i++;
	}
	printf("\n");
	*/
	// Errors do not correspond to bash errors yet
	while (sh->redirs[i] != -1)
	{
		if (sh->redirs[i] == 1)
		{
			in_fd = open(sh->cmd[i][1], O_RDONLY);
			if (in_fd == -1)
			{
				printf("minishell: %s: No such file or directory\n", sh->cmd[i + 1]);
				sh->status = 1;
				return ;
			}
			else if (dup2(in_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 fail infile");
				sh->status = 1;
			}
			close(in_fd);
		}
		else if (sh->redirs[i] == 2)
		{
			out_fd = open(sh->cmd[i][1], O_WRONLY);
			if (in_fd == -1)
			{
				printf("minishell: %s: No such file or directory\n", sh->cmd[i + 1]);
				sh->status = 1;
				return ;
			}
			else if (dup2(out_fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 fail outfile");
				sh->status = 1;
			}
			close(out_fd);
		}
		else if (sh->redirs[i] == 3)
		{
			out_fd = open(sh->cmd[i][2], O_APPEND);
			if (in_fd == -1)
			{
				printf("minishell: %s: No such file or directory\n", sh->cmd[i + 1]);
				sh->status = 1;
				return ;
			}
			else if (dup2(out_fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 fail outfile append");
				sh->status = 1;
			}
			close(out_fd);
		}
		i++;
	}
	printf("\n");
}
