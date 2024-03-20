/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:09:54 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/15 11:03:41 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_put_hex(unsigned int num, const char format)
{
	int	ret;

	ret = 0;
	if (num >= 16)
	{
		ret += ft_put_hex(num / 16, format);
		ret += ft_put_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ret += ft_print_char(num + '0');
		else
		{
			if (format == 'x')
				ret += ft_print_char(num - 10 + 'a');
			if (format == 'X')
				ret += ft_print_char(num - 10 + 'A');
		}
	}
	return (ret);
}

int	ft_print_hex(int num, const char format)
{
	int	ret;

	ret = 0;
	if (num == 0)
		ret = write(1, "0", 1);
	else
		ret = ft_put_hex(num, format);
	return (ret);
}
