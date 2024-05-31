/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:09:11 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/31 15:15:31 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_inside_quote(t_shell *sh, int i, char quote)
{
	while (sh->input[i] != quote && sh->input[i] != '\0')
		i++;
	if (sh->input[i] != quote)
	{
		errprompt("", "wrong amount of quotes", NULL, sh);
		return (-1);
	}
	return (i);
}

int	quote_count(t_shell *sh)
{
	int	i;
	int	quotecount;
	int	squotecount;

	i = 0;
	quotecount = 0;
	squotecount = 0;
	while (sh->input[i] != '\0')
	{
		if (sh->input[i] == '\'')
			i = check_inside_quote(sh, i + 1, '\'');
		else if (sh->input[i] == '\"')
			i = check_inside_quote(sh, i + 1, '\"');
		if (i == -1)
			return (-1);
		i++;
	}
	return (0);
}
