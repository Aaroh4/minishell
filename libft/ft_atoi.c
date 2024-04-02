/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:31:09 by ahamalai          #+#    #+#             */
/*   Updated: 2023/11/13 11:04:34 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	overflowfix(int neg)
{
	if (neg == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long int	ret;
	long int	old_ret;
	int			neg;

	neg = 1;
	ret = 0;
	while (*str == ' ' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		old_ret = ret;
		ret = ret * 10 + (*str - 48);
		if (old_ret > ret)
			return (overflowfix(neg));
		str++;
	}
	return ((int)ret * neg);
}
