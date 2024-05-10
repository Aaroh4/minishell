/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:56:49 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/10 10:58:09 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	long int	num;

	i = count(n);
	num = n;
	str = (char *)db_malloc(i + 1);
	if (str == 0)
		return (0);
	str[i] = '\0';
	if (num < 0)
		num *= -1;
	while (i > 0)
	{
		i--;
		str[i] = (num % 10) + '0';
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
