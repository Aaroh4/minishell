/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinshelpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:31:14 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/30 11:31:30 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_exit(t_cmdn *node, int i, int j)
{
	int	check;

	check = 0;
	while (node->cargs[1][i] != '\0')
		i++;
	if (node->cargs[1][j] == '-')
	{
		check = 1;
		j++;
	}
	while (ft_isdigit(node->cargs[1][j]) && node->cargs[1][j] != '\0')
		j++;
	if ((j == i && j < 19) || (j == i && j < 20 && check == 1))
		j = ft_atoi(node->cargs[1]);
	else
	{
		printf("exit: %s: numeric argument required\n", node->cargs[1]);
		j = 255;
	}
	return (j);
}
