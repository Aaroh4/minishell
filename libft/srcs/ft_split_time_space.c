/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_time_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:03:00 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/23 16:18:33 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_wording(char *dest, int *i, int *j, char const *s)
{
	dest[*i] = s[*i];
	(*i)++;
	*j = *i;
	while (s[*i] != '|' && s[*i] != '\0')
		(*i)++;
	dest[*i] = '\0';
	(*i)--;
	while (*i >= *j)
	{
		dest[*i] = s[*i];
		(*i)--;
	}
}

static void	do_word(char *dest, char const *s, char c, int check)
{
	int	i;
	int	j;

	i = 0;
	if (check == 0 && (s[i] == '\"' || s[i] == '\''))
		i++;
	else if (s[i] == '\"' || s[i] == '\'')
	{
		ft_wording(dest, &i, &j, s);
		return ;
	}
	while (s[i] != c && s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
}

static int	do_split(char **arr, char const *s, char c, int i)
{
	int	jcheck[2];
	int	word;

	word = 0;
	jcheck[0] = 0;
	jcheck[1] = 0;
	while (s[i] != '\0')
	{
		jcheck[0] = ft_checker(s, i, jcheck[0]);
		if (s[i] == c)
			i++;
		else
		{
			jcheck[1] = ft_incrj(i, s, jcheck[0], c);
			if ((s[i] == '\"' || s[i] == '\'') && jcheck[0] != 1)
				i += jcheck[1];
			else
			{
				arr[word] = (char *)malloc(sizeof(char) * (jcheck[1] + 2));
				if (!arr[word])
					return (freemem(arr, word));
				do_word(arr[word++], s + i, c, jcheck[0]);
				i += jcheck[1];
			}
		}
	}
	return (0);
}

int	wordcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((s[i] == '\"' || s[i] == '\'') && s[i - 1] != '\\')
			i = ft_check(i, s);
		if ((s[i] != c && s[i + 1] == c)
			|| (s[i + 1] == '\0' && s[i] != c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split_time_space(char const *s, char c)
{
	int		count;
	char	**arr;
	int		i;

	i = 0;
	count = wordcount(s, c);
	if (count == -1)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	arr[count] = NULL;
	if (do_split(arr, s, c, i) == -1)
		return (NULL);
	return (arr);
}
