/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:10:17 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/10 10:54:17 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = db_malloc(count * size);
	if (p == NULL)
		return (0);
	ft_bzero(p, size * count);
	return (p);
}
