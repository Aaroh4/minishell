/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 12:09:30 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/25 09:22:16 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	ft_check_for_other(char *breakchar)
{
	int	i;

	i = 0;
	while (breakchar[i] != ' ' && breakchar[i] != '\0')
		i++;
	while (breakchar[i] == ' ' && breakchar[i] != '\0')
		i++;
	if (breakchar[i] != '<')
		return (1);
	while ((breakchar[i] == '<' && breakchar[i] != '\0') || (breakchar[i] == ' '
			&& breakchar[i] != '\0'))
		i++;
	while (breakchar[i] != ' ' && breakchar[i] != '\0')
		i++;
	if (breakchar[i] != '\0')
		return (1);
	return (0);
}

char	*ft_heredoc(char *breakchar, int hdocs)
{
	char	*buf;
	char	*astr;
	int		i;
	int		j;
	int		check;

	buf = NULL;
	astr = malloc(1);
	astr = "\0";
	i = 0;
	j = 0;
	check = ft_check_for_other(breakchar);
	while (breakchar[i] != '\0')
	{
		if (breakchar[i] == '<' && breakchar[i + 1] == '<' && breakchar[i
			+ 2] != '<')
		{
			j++;
			if (j == hdocs)
				break ;
		}
		i++;
	}
	if (breakchar[i] != ' ')
		breakchar = ft_substr(breakchar, i + 2, sizeof(breakchar) - i - 3);
	while (1)
	{
		write(1, "> ", 2);
		buf = get_next_line(0);
		// if (!buf)
			// ERROR CHECK HERE DO NOT MISS THIS ONE BEFORE SENDING BACK THIS PROJECT!!!#!!#:LKJHGC
		if (!ft_strncmp(breakchar, buf, ft_strlen(breakchar))
			&& ft_strncmp("\n", buf, 2))
			break ;
		if (j == hdocs)
			astr = ft_strjoin(astr, buf);
		free(buf);
	}
	free(buf);
	free(breakchar);
	if (check == 1)
		return (NULL);
	return (astr);
}
