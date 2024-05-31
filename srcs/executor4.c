/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:27:05 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/30 09:35:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler_child2(int signum)
{
	(void)signum;
	write(2, "Quit: 3", 7);
	write(1, "\n", 1);
}

void	ft_handler_child(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}
