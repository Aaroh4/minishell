/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:30:47 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:09:19 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*pc;

	pc = (char *)dst;
	if (!dst && !src)
		return (0);
	while (n > 0)
	{
		*pc = *(char *)src;
		pc++;
		src++;
		n--;
	}
	return (dst);
}
