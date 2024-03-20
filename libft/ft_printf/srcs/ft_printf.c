/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:30:18 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/17 14:01:39 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

int	eval_format(const char *inputstr, va_list args)
{
	int	ret;

	ret = 0;
	if (*inputstr == 'c')
		ret += ft_print_char(va_arg(args, int));
	if (*inputstr == 's')
		ret += ft_print_string(va_arg(args, char *));
	if (*inputstr == 'p')
		ret += ft_print_addr(va_arg(args, void *));
	if (*inputstr == 'd' || *inputstr == 'i')
		ret += ft_print_int(va_arg(args, int));
	if (*inputstr == 'u')
		ret += ft_print_uint(va_arg(args, unsigned int));
	if (*inputstr == 'x' || *inputstr == 'X')
		ret += ft_print_hex(va_arg(args, int), *inputstr);
	return (ret);
}

int	ft_printf(const char *inputstr, ...)
{
	unsigned int	i;
	va_list			args;

	i = 0;
	va_start(args, inputstr);
	while (*inputstr != '\0')
	{
		if (*inputstr == '%')
		{
			if (*inputstr == '%' && *(inputstr + 1) == '\0')
				break ;
			inputstr++;
			if (ft_strchr("cspdiuxX", *inputstr))
				i += eval_format(inputstr, args);
			else if (*inputstr == '%')
				i += ft_print_char('%');
		}
		else
			i += ft_print_char(*inputstr);
		inputstr++;
	}
	va_end(args);
	return (i);
}
