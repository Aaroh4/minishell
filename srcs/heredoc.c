/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:09:30 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/09 14:30:41 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_breakchar(char *breakchar, int *i, int *j, int hdocs)
{
	int	k;
	char	*temp;

	while (breakchar[*i] != '\0')
	{
		if (breakchar[*i] == '<' && breakchar[*i + 1] == '<'
			&& breakchar[*i + 2] != '<')
		{
			*j += 1;
			if (*j == hdocs)
				break ;
		}
		*i += 1;
	}
	k = *i + 2;
	while (breakchar[k] != '\0' && breakchar[k] != '<')
		k++;
	if (breakchar[*i] != ' ')
		breakchar = ft_substr(breakchar, *i + 2, k - *i - 2);
	temp = ft_strjoin(breakchar, "\n");
	free(breakchar);
	return (temp);
}

int	heredoc_loop(char **astr, char *breakchar, int j, int hdocs)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
			// if (!buf) // ERROR CHECK HERE DO NOT MISS THIS ONE BEFORE SENDING BACK THIS PROJECT!!!#!!#:LKJHGC
		if (buf == NULL)
			return (0);
		if (!ft_strncmp(breakchar, buf, ft_strlen(breakchar)))
			break ;
		if (j == hdocs)
			*astr = ft_strjoin(*astr, buf);
		free(buf);
	}
	free(buf);
	return (1);
}

void	ft_handler_heredoc(int signum)
{
	signum = 1;
	write(1, "\n> ", 3);
}

char	*ft_heredoc(char *breakchar, int hdocs)
{
	char	*astr;
	int		i;
	int		j;
	char	*temp;

	signal(SIGINT, ft_handler_heredoc);
	astr = malloc(1);
	astr = "\0";
	i = 0;
	j = 0;
	temp = make_breakchar(breakchar, &i, &j, hdocs);
	free(breakchar);
	if (heredoc_loop(&astr, temp, j, hdocs) == 0)
	{
		return (NULL);
		free(temp);
	}
	free(temp);
	if (astr[0] == '\0')
		return (ft_strjoin(astr, "\0"));
	return (astr);
}
