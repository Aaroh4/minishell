/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:00:12 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:07:28 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	callend(char const *s1, char const *set)
{
	int	i;
	int	i2;

	i = 0;
	i2 = ft_strlen(s1);
	while (i < i2)
	{
		if (ft_strrchr(set, s1[i2 - i]) == 0)
			break ;
		i++;
	}
	return (i2 - i + 1);
}

int	callstart(char const *s1, char const *set)
{
	int	i;
	int	i2;

	i = 0;
	i2 = ft_strlen(s1);
	while (i < i2)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = callstart(s1, set);
	end = callend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
