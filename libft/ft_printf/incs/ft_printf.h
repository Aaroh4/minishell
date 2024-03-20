/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:46:00 by mburakow          #+#    #+#             */
/*   Updated: 2023/12/18 13:33:46 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../../libft/libft.h"

typedef struct s_print
{
	va_list	args;
	int		wdt;
	int		prc;
	int		zero;
	int		pnt;
	int		dash;
	int		tl;
	int		sign;
	int		is_zero;
	int		perc;
	int		spc;
}			t_print;

int			ft_printf(const char *formstr, ...);
int			ft_print_char(char c);
int			ft_print_string(char *str);
int			ft_print_addr(void *ptr);
int			ft_print_int(int dec);
int			ft_print_uint(unsigned int num);
int			ft_print_hex(int num, const char format);

#endif
