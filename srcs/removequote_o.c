/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:21:59 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/31 13:54:17 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



char	*remove_quote_level(char *str, t_shell *sh)
{
	int		i;
	char	*cursor;
	char	*res;

	i = 1;
	cursor = str;
	while (cursor != '\0')
	{
		if (cursor == '\"' || cursor == '\'') 
		{
			if (ft_strcpos(*cursor, cursor + 1))
			{
				dprintf(2, "Found\n");
			}

		}
		cursor++;
	}
	dprintf(2, "sh->ntype: %s\n");
	return (str);
}