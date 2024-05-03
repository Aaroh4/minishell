/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:20:12 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/03 20:15:46 by mburakow         ###   ########.fr       */
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
				// Try to open the file and redirect input
 			}
			else if (sh->cmd[i][j - 1] != '>' && 
				sh->cmd[i][j] == '>' && 
				sh->cmd[i][j + 1] != '>')
			{
				sh->redirs[i] = 2;
				// Try to create/open the file in replace mode and redirect input
			}
			else if (sh->cmd[i][j + 1] != '>' && 
				sh->cmd[i][j] == '>' && 
				sh->cmd[i][j + 1] == '>' &&
				sh->cmd[i][j + 1] != '>')
			{
				sh->redirs[i] = 3;
				// Try to create/open the file in append mode and redirect input
			}
			j++;
		}
		i++;
	}
	i = 0;
	printf("Redirs:");
	while (sh->redirs[i] != -1)
	{
		printf(" %d", sh->redirs[i]);
		i++;
	}
	printf("\n");
}

/*
static void	get_heredocs(t_shell *sh)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (sh->cmd[i] != NULL)
	{
		j = 0;
		while (sh->cmd[i][j] != '\0')
		{
			if (sh->cmd[i][j] == '<' && sh->cmd[i][j + 1] == '<'
				&& sh->cmd[i][j + 2] != '<' && sh->cmd[i][j + 2] != '\0')
			{
				sh->hdocs[i]++;
				temp = ft_heredoc(sh->cmd[i], sh->hdocs[i]);
			}
			j++;
		}
		if (sh->hdocs[i] > 0)
			sh->cmd[i] = temp;
		i++;
	}
}

char	*ft_give_fixed(char *str, int *i, char *temp)
{
	char	*temp2;
	int		j;

	j = 0;
	temp2 = malloc(sizeof(char) * ft_strlen(str) + ft_strlen(temp) + 1);
	while (temp[j] != '\0')
	{
		temp2[j] = temp[j];
		j++;
	}
	while (str[*i] != '\0')
	{
		if (str[*i] != '<' && str[*i - 1] == '<' && str[*i - 2] == '<')
			while (str[*i] == ' ')
				*i += 1;
		temp2[j] = str[*i];
		*i += 1;
		j += 1;
	}
	temp2[j] = '\0';
	return (temp2);
}

char	*ft_fix_for_space(char *str)
{
	int		i;
	int		j;
	int		hdocs;
	char	*temp;

	i = 0;
	hdocs = 0;
	while (str[i++] != '\0')
		if (str[i - 1] != '<'
			&& str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			hdocs++;
	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * ft_strlen(str) + hdocs + 1);
	while (str[i] != '\0')
	{
		if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] == '<' && str[i
				+ 2] != '<')
		{
			temp[j] = ' ';
			j++;
		}
		temp[j++] = str[i++];
	}
	temp[j] = '\0';
	return (temp);
}

char	*ft_make_easy_heredoc(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	str = ft_fix_for_space(str);
	temp = malloc(sizeof(char) * ft_strlen(str) + 2);
	while (str[i] != '\0')
	{
		if (str[i - 1] != '<'
			&& str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
			return (ft_give_fixed(str, &i, temp));
		else
		{
			temp[j] = str[i];
			i++;
			j++;
		}
	}
	temp[j] = '\0';
	return (temp);
}

*/