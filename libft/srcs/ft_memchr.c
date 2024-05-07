/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 11:46:15 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:06:51 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	f;

	i = 0;
	str = (unsigned char *)s;
	f = (unsigned char)c;
	while (i != n)
	{
		if (str[i] == f)
			return (&str[i]);
		i++;
	}
	return (0);
}
