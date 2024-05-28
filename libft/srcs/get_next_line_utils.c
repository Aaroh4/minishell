/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:06:43 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/28 13:34:37 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_chr(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	if (str[i] == '\n')
		count++;
	return (count);
}

char	*ft_strrdup(const char *src)
{
	char	*str;
	int		i;
	int		ai;

	i = 0;
	ai = 0;
	while (src[ai])
	{
		ai++;
	}
	ai++;
	str = malloc(sizeof(char) * ai);
	ai--;
	if (str == 0)
		return (0);
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strrjoin(char const *s1, char const *s2)
{
	int		i;
	int		ei;
	char	*s;

	i = 0;
	ei = 0;
	s = malloc(ft_strrlen(s1) + ft_strrlen(s2) + 1);
	if (s == NULL)
		return (0);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[ei])
	{
		s[i] = s2[ei];
		i++;
		ei++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_subbstr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	while (*s && start--)
		s++;
	ret = malloc(len + 1);
	if (!ret)
		return (0);
	ret[len] = '\0';
	while (len--)
		ret[len] = s[len];
	return (ret);
}

int	ft_strrlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
