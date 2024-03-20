/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:42:49 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/09 18:55:18 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	check_off(unsigned long num, int neg, char str)
{
	if (num >= LONG_MAX / 10 && (num > LONG_MAX / 10 || (str - '0') > LONG_MAX
			% 10))
	{
		if (neg == 1)
			return (-1);
		else if (neg == -1)
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int				neg;
	int				i;
	unsigned long	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (check_off(num, neg, (char)str[i]) != 1)
			return (check_off(num, neg, (char)str[i]));
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}
