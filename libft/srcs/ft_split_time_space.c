/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_time_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:03:00 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/24 15:22:06 by mburakow         ###   ########.fr       */
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

/*
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
*/

// If a quote has been found, checks for matching quote.
// If a matching quote is not found, returns original index.
// Otherwise returns index of matching quote.
int	quote_check(int i, const char *str, char q)
{
	int	orig;

	orig = i;
	while (str[i] != '\0')
	{
		if (str[i] == q && str[i - 1] != '\\')
			return (i);
		i++;
	}
	return (orig);
}

static void write_word(const char *src, char *word, int i, int j)
{
	int	k;

	k = 0;
	while (src[i] != '\0' && i != j)
		word[k++] = src[i++];
	word[k] = '\0';
}

static int	do_split(char **arr, char const *s, char c, int i)
{
	int	j;
	int	word;

	word = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
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
			if (j > i)
			{	
				arr[word] = (char *)malloc(sizeof(char) * ((j - i) + 1));
				if (!arr[word])
					return (freemem(arr, word));
				else
				{
					write_word(s, arr[word], i, j);
					word++;
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
	// dprintf(2, "count was %d\n", count);

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
