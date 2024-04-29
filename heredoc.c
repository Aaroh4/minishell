/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:09:30 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/26 14:40:23 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*make_breakchar(char *breakchar, int *i, int *j, int hdocs)
{
	int	k;

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
	breakchar = ft_strjoin(breakchar, "\n");
	return (breakchar);
}

char	*ft_heredoc(char *breakchar, int hdocs)
{
	char	*buf;
	char	*astr;
	int		i;
	int		j;

	buf = NULL;
	astr = malloc(1);
	astr = "\0";
	i = 0;
	j = 0;
	breakchar = make_breakchar(breakchar, &i, &j, hdocs);
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
			// if (!buf) // ERROR CHECK HERE DO NOT MISS THIS ONE BEFORE SENDING BACK THIS PROJECT!!!#!!#:LKJHGC
		if (!ft_strncmp(breakchar, buf, ft_strlen(breakchar)))
			break ;
		if (j == hdocs)
			astr = ft_strjoin(astr, buf);
		free(buf);
	}
	free(buf);
	free(breakchar);
	return (astr);
}
