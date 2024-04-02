/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:32:15 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:05:09 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	ei;

	i = 0;
	ei = 0;
	if (*needle == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		ei = 0;
		while (haystack[i + ei] == needle[ei] && i + ei < len)
		{
			if (needle[ei + 1] == '\0')
				return (&((char *)haystack)[i]);
			ei++;
		}
		i++;
	}
	return (0);
}
