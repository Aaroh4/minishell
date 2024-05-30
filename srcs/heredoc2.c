/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:44:35 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/29 12:51:25 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler_heredoc(int signum)
{
	signum = 0;
	write(1, "\n", 1);
	exit(0);
}

void	if_loop(int i, char quote, char *str, t_bool in_quotes)
{
	int	j;

	j = i;
	quote = str[i];
	in_quotes = TRUE;
	while (str[j] != '\0')
	{
		str[j] = str[j + 1];
		j++;
	}
	while (str[i] != '\0' && str[i] != quote)
		i++;
	if (str[i] == quote)
	{
		j = i;
		while (str[j] != '\0')
		{
			str[j] = str[j + 1];
			j++;
		}
	}
	in_quotes = FALSE;
}

void	remove_breakchar_quotes(char *str)
{
	int		i;
	char	quote;
	t_bool	in_quotes;

	i = 0;
	in_quotes = FALSE;
	quote = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			if_loop(i, quote, str, in_quotes);
		else
			i++;
	}
}

void	free_breakchar_temp(char *breakchar, char *temp)
{
	free(breakchar);
	free(temp);
}
