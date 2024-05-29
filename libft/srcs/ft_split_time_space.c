/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_time_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:03:00 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/29 11:47:56 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	write_word(const char *src, char *word, int i, int j)
{
	int	k;

	k = 0;
	while (src[i] != '\0' && i != j)
		word[k++] = src[i++];
	word[k] = '\0';
}

int	else_while(int i, char c, char const *s)
{
	int	j;

	j = i;
	while (s[j] != c && s[j] != '\0')
	{
		if ((s[j] == '\"' || s[j] == '\'') && (j == 0 || s[j - 1] != '\\'))
		{
			j++;
			j = quote_check(j, s, s[j - 1]);
		}
		j++;
	}
	return (j);
}

static int	do_split(char **arr, char const *s, char c, int i)
{
	int	word;
	int	j;

	word = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			j = else_while(i, c, s);
			if (j > i)
			{
				arr[word] = (char *)malloc(sizeof(char) * ((j - i) + 1));
				if (!arr[word])
					return (freemem(arr, word));
				else
				{
					write_word(s, arr[word++], i, j);
					i = j + 1;
				}
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
		while (s[i] == c)
			i++;
		if ((s[i] == '\"' || s[i] == '\'') && (i == 0 || s[i - 1] != '\\'))
		{
			i++;
			i = quote_check(i, s, s[i - 1]);
		}
		if (s[i] != c && (s[i + 1] == c || (s[i + 1] == '\0')))
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
	if (do_split(arr, s, c, i) == -1)
		return (NULL);
	arr[count] = NULL;
	return (arr);
}
