/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:20:01 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/20 07:48:37 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <stdio.h>
#include "libft.h"

static char	**alloc_words(const char *s, char c, char **split_str);
static char	*make_word(const char *s, char c);
static char	**alloc_wlen(const char *s, char c, char **split_str);
static void	free_split(char **split_str, int index);

char	**ft_split(char const *s, char c)
{
	char	**split_str;

	if (!s)
		return (NULL);
	// dprintf(2, "str to split: #%s#, length: %d\n", s, ft_strlen(s));
	if (s == NULL || s[0] == '\0')
	{
		split_str = (char **)malloc(sizeof(char *) * 2);
		split_str[0] = (char *)malloc(sizeof(char));
		split_str[0][0] = '\0';
		split_str[1] = NULL;
		// dprintf(2, "returning...\n");
		return (split_str);
	}
	// dprintf(2, "not returning...\n");
	split_str = NULL;
	split_str = alloc_words(s, c, split_str);
	if (split_str == NULL)
		return (NULL);
	split_str = alloc_wlen(s, c, split_str);
	if (split_str == NULL)
		return (NULL);
	return (split_str);
}

static char	**alloc_words(const char *s, char c, char **split_str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
			words++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	split_str = malloc((words + 1) * sizeof(char *));
	if (split_str == NULL)
		return (NULL);
	split_str[words] = 0;
	return (split_str);
}

static char	*make_word(const char *s, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	word = malloc((i + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	word[i] = '\0';
	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

static char	**alloc_wlen(const char *s, char c, char **split_str)
{
	int		index;
	int		i;

	i = 0;
	index = -1;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			index++;
			split_str[index] = make_word((char *)&s[i], c);
			if (split_str[index] == NULL)
			{
				free_split(split_str, index);
				return (NULL);
			}
			i++;
		}
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (split_str);
}

static void	free_split(char	**split_str, int index)
{
	while (index > 0)
	{
		index--;
		free(split_str[index]);
	}
	free(split_str);
}
