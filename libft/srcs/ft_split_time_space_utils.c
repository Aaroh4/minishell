/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_time_space_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:41:47 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/23 16:17:01 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

int	ft_check(int i, const char *str)
{
	if (str[i] == '\"' || str[i] == '\'')
	{
		i++;
		while (str[i] != '|' && str[i] != '\0')
			i++;
		while (str[i] != '\"' && str[i] != '\'')
			i--;
	}
	return (i);
}

int	freemem(char **arr, int size)
{
	while (size--)
		free(arr[size]);
	free(arr);
	return (-1);
}

int	ft_checker(char const *s, int i, int check)
{
	if ((s[i] == '\"' || s[i] == '\'') && !check)
		return (1);
	return (0);
}

int	ft_incrj(int i, char const *s, int check, char c)
{
	int	j;

	j = 0;
	if ((s[i] == '\"' || s[i] == '\'') && check == 1)
	{
		while (s[i + j + 1] != '|' && s[i + j + 1] != '\0')
			j++;
		while (s[i + j] != '\"' && s[i + j] != '\'')
			j--;
		i++;
	}
	else
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
	return (j);
}
