/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:27:05 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/28 16:27:22 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler_child2(int signum)
{
	signum = 0;
	write(2, "Quit: 3", 7);
	write(1, "\n", 1);
}

void	ft_handler_child(int signum)
{
	signum = 0;
	write(1, "\n", 1);
}
