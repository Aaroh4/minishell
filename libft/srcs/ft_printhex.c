/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:23:17 by ahamalai          #+#    #+#             */
/*   Updated: 2024/02/14 16:57:58 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (str[i])
	{
		i += ft_putchar(str[i]);
		if (i < 0)
			return (-1);
	}
	return (i);
}

int	count(int n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

int	ft_printhex(long n, int base, char c)
{
	int		count;
	char	*symbols;

	if (c == 'X')
		symbols = "0123456789ABCDEF";
	else
		symbols = "0123456789abcdef";
	if (n < 0)
	{
		if (write(1, "-", 1) < 0)
			return (-1);
		return (ft_printhex((n * -1), base, c) + 1);
	}
	else if (n < base)
		return (ft_putchar(symbols[n]));
	else
	{
		count = ft_printhex(n / base, base, c);
		if (count < 0)
			return (-1);
		return (count + ft_printhex(n % base, base, c));
	}
}

int	ft_printptr(unsigned long n)
{
	int		count;
	char	*symbols;

	symbols = "0123456789abcdef";
	count = 0;
	count += ft_putstr("0x");
	if (count < 0)
		return (-1);
	if (n < 16)
		return (count += ft_putchar(symbols[n]));
	count += (ft_printhex((n / 16), 16, 'x'));
	return (count + ft_printhex(n % 16, 16, 'x'));
}
