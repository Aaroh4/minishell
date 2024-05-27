/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:17:33 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/27 11:17:38 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	quote_check(int i, const char *str, char q)
{
	int	orig;

	orig = i;
	while (str[i] != '\0' && str[i - 1] != '\\')
	{
		if (str[i] == q)
			return (i);
		i++;
	}
	return (orig);
}
