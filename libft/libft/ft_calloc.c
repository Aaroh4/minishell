/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:48:15 by mburakow          #+#    #+#             */
/*   Updated: 2023/11/08 07:59:05 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*objs;
	size_t	magic_number;

	magic_number = 0 - 1;
	if (count && size && count > (magic_number / size))
		return (NULL);
	objs = malloc(size * count);
	if (objs == NULL)
		return (NULL);
	ft_bzero(objs, size * count);
	return (objs);
}
