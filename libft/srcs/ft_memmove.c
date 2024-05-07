/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:59:57 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:10:48 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*psrc;
	char	*pdst;
	size_t	i;

	psrc = (char *)src;
	pdst = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (0);
	if (pdst > psrc)
	{
		while (len-- > 0)
			pdst[len] = psrc[len];
	}
	else
	{
		while (i < len)
		{
			pdst[i] = psrc[i];
			i++;
		}
	}
	return (dst);
}
