/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:30:33 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/09 19:58:30 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	get_len(long num)
{
	int	len;

	len = 0;
	if (num <= 0)
		len++;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

static char	*make_string(int len, long num)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = '0' + (num % 10);
		num = (num / 10);
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	long	num;
	int		sign;
	char	*str;

	num = (long)n;
	sign = 1;
	len = get_len(num);
	if (num < 0)
	{
		sign *= -1;
		num *= -1;
	}
	str = make_string(len, num);
	if (!str)
		return (NULL);
	if (sign == -1)
		str[0] = '-';
	return (str);
}
