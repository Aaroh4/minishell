/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_db_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:34:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/10 10:42:45 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

// Just an lldb'able malloc
void	*db_malloc(size_t size)
{
	return (malloc(size));
}