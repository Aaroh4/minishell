/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_time_space_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:41:47 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/12 13:06:24 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(int i, const char *str)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] != '|' && str[i] != '\0')
			i++;
		while (str[i] != '\"')
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
	if (s[i] == '\"' && !check)
		return (1);
	return (0);
}

int	ft_incrj(int i, char const *s, int check, char c)
{
	int	j;

	j = 0;
	if (s[i] == '\"' && check == 1)
	{
		while (s[i + j + 1] != '|' && s[i + j + 1] != '\0')
			j++;
		while (s[i + j] != '\"')
			j--;
		i++;
	}
	else
		while (s[i + j] != c && s[i + j] != '\0')
			j++;
	return (j);
}