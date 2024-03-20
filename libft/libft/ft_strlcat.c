/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:11:33 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/09 18:51:49 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	dlen;

	if ((dst == NULL || src == NULL) && dstsize == 0)
		return (0);
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen((char *)src));
	i = 0;
	j = 0;
	len = dstsize - ft_strlen(dst) - 1;
	dlen = ft_strlen(dst);
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < len)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	return (dlen + ft_strlen((char *)src));
}
