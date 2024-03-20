/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:08:18 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/08 09:07:55 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_getstart(const char *s1, const char *set);
static size_t	ft_getend(const char *s1, const char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	newlen;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (end && end >= start)
		newlen = end - start + 1;
	else
		newlen = 0;
	new = (char *)malloc(sizeof(char) * newlen + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < newlen)
	{
		new[i] = s1[start + i];
		i++;
	}
	new[newlen] = '\0';
	return (new);
}

static size_t	ft_getstart(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static size_t	ft_getend(const char *s1, const char *set)
{
	size_t	i;

	i = ft_strlen((char *)s1) + 1;
	while (i > 0)
	{
		i--;
		if (ft_strchr(set, s1[i]) == 0)
			break ;
	}
	return (i);
}
