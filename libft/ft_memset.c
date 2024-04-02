/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:31:29 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:11:40 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*pc;

	i = 0;
	pc = b;
	while (i != len)
	{
		*pc = c;
		pc++;
		i++;
	}
	return (b);
}
