/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:09:30 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/16 15:51:38 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	*ft_heredoc(char *breakchar)
{
	char	*buf;
	char	*astr;
	int		i;

	buf = NULL;
	astr = malloc(0);
	i = 0;
	while (breakchar[i] != '\0')
	{
		if (breakchar[i] == '<' && breakchar[i + 1] == '<'
			&& breakchar[i + 2] != '<')
		{
			astr = ft_strjoin(astr, ft_substr(breakchar, 0, i));
			astr = ft_strjoin(astr, "'");
			break ;
		}
		i++;
	}
	if (breakchar[i + 2] != ' ')
		breakchar = ft_substr(breakchar, i + 2, sizeof(breakchar) - i + 2);
	else
		breakchar = ft_substr(breakchar, i + 3, sizeof(breakchar) - i + 3);
	while (1)
	{
		write(1, "heredoc>", 9);
		buf = get_next_line(0);
		// if (!buf) // ERROR CHECK HERE DO NOT MISS THIS ONE BEFORE SENDING BACK THIS PROJECT!!!#!!#:LKJHGC
		if (!ft_strncmp(breakchar, buf, ft_strlen(buf) - 1))
			break ;
		astr = ft_strjoin(astr, buf);
		astr = ft_strjoin(astr, "'");
		free(buf);
	}
	free(buf);
	return (astr);
}
