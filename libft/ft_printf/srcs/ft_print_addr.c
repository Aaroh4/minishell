/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:35:16 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/16 11:09:44 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	ft_put_addr(unsigned long long addr)
{
	int	ret;

	ret = 0;
	if (addr >= 16)
	{
		ret += ft_put_addr(addr / 16);
		ret += ft_put_addr(addr % 16);
	}
	else
	{
		if (addr <= 9)
			ret += ft_print_char(addr + '0');
		else
			ret += ft_print_char(addr - 10 + 'a');
	}
	return (ret);
}

int	ft_print_addr(void *ptr)
{
	int	ret;

	ret = 0;
	ret += write(1, "0x", 2);
	ret += ft_put_addr((unsigned long long)ptr);
	return (ret);
}
