/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:44:35 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/30 09:42:03 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Assignment does not silence compiler warnings, cast does.
void	ft_handler_heredoc(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	exit(0);
}

static void	skip_quote_loop(int i, char *str)
{
	int		j;
	char	quote;

	j = i;
	quote = str[i];
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
}

void	remove_breakchar_quotes(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			skip_quote_loop(i, str);
		else
			i++;
	}
}

void	free_breakchar_temp(char *breakchar, char *temp)
{
	free(breakchar);
	free(temp);
}
