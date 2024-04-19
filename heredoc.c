/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:09:30 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/19 12:48:46 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*ft_heredoc(char *breakchar, int hdocs)
{
	char	*buf;
	char	*astr;
	int		i;
	int		j;
	int		k;

	buf = NULL;
	i = 0;
	j = 0;
	while (breakchar[i] != '\0')
	{
		if (breakchar[i] == '<' && breakchar[i + 1] == '<'
			&& breakchar[i + 2] != '<')
		{
			j++;
			if (j == 1)
				astr = ft_substr(breakchar, 0, i);
			if (j == hdocs)
				k = i;
		}
		i++;
	}
	if (breakchar[k + 2] != ' ')
		breakchar = ft_substr(breakchar, k + 2, sizeof(breakchar) - k + 2);
	else
		breakchar = ft_substr(breakchar, k + 3, sizeof(breakchar) - k + 3);
	while (1)
	{
		write(1, "> ", 9);
		buf = get_next_line(0);
			// if (!buf) // ERROR CHECK HERE DO NOT MISS THIS ONE BEFORE SENDING BACK THIS PROJECT!!!#!!#:LKJHGC
		if (!ft_strncmp(breakchar, buf, ft_strlen(buf) - 1))
			break ;
		if (j == hdocs)
			astr = ft_strjoin(astr, buf);
		free(buf);
	}
	free(buf);
	free(breakchar);
	return (astr);
}
