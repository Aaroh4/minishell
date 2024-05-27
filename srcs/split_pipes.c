/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:04:33 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/27 22:10:44 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

static int	word_count(char *str, char *charset)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		i = skip_quotes(str, i);
		if (is_separator(str[i], charset) == 0
			&& is_separator(str[i + 1], charset) == 1)
			count++;
		i++;
	}
	return (count);
}

static void	do_split(char **arr, char *str, char *charset)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (is_separator(str[i], charset) == 1)
			i++;
		else
		{
			j = 0;
			while (is_separator(str[i + j], charset) == 0)
			{
				j = skip_quotes(str, i + j) - i;
				//if (str[i + j] == '\0')
				//	break ;
				j++;
			}
			// dprintf(2, "j was %d\n", j);
			arr[word] = (char *)malloc(sizeof(char) * (j + 1));
			ft_memcpy(arr[word], &str[i], j);
			i += j;
			word++;
		}
	}
}

char	**split_pipes(char *str, char *charset)
{
	int		count;	
	char	**arr;

	if (str == NULL || str[0] == '\0')
	{
		arr = (char **)malloc(sizeof(char *) * 2);
		arr[0] = (char *)malloc(sizeof(char));
		arr[0][0] = '\0';
		arr[1] = NULL;
		return (arr);
	}
	count = word_count(str, charset);
	// dprintf(2, "Count was: %d\n", count);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	arr[count] = NULL;
	do_split(arr, str, charset);
	// print_char_array(arr);
	return (arr);
}
