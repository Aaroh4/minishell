/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:16:14 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/27 12:17:50 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_space(char *c)
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

void	trim_outputs(char *c)
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

void	trim_inputs(char *c)
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
	return (cmd);
}
