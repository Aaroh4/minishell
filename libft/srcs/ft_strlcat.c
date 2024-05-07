/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:56:12 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:07:13 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	ei;

	i = 0;
	ei = 0;
	while (dst[i] && i < dstsize)
		i++;
	while (src[ei] && i + ei + 1 < dstsize)
	{
		dst[i + ei] = src[ei];
		ei++;
	}
	if (i + ei != dstsize)
		dst[i + ei] = '\0';
	return (i + ft_strlen(src));
}
