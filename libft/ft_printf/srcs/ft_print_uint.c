/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:11:39 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/15 20:26:43 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_print_uint(unsigned int num)
{
	int	ret;

	ret = 0;
	if (num > 9)
	{
		ret += ft_print_uint(num / 10);
		ret += ft_print_uint(num % 10);
	}
	else
		ret += ft_print_char(num + '0');
	return (ret);
}
