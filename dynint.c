/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:24:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/05 15:27:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_dynint*	create_dynamic_int_array(void) 
{
	t_dynint *dynarr;
	
	dynarr = (t_dynint*)malloc(sizeof(t_dynint));
	if (dynarr == NULL)
		exit(1);
	dynarr->array = (int*)ft_calloc(INITIAL_SIZE, sizeof(int));
	if (dynarr->array == NULL) 
	{
		free(dynarr);
		exit(1);
	}
	dynarr->size = 0;
	dynarr->capacity = INITIAL_SIZE;
	return (dynarr);
}

void	expand_dynamic_int_array(t_dynint *dynarr) 
{
	size_t	new_capacity;
	int		*newarr;
	int 	*temp;
	int		i;

	new_capacity = dynarr->capacity * 2;
	newarr = (int*)ft_calloc(new_capacity, sizeof(int));
	if (newarr == NULL) 
	{
		free(dynarr->array);
		free(dynarr);
		exit(1);
	}
	i = 0;
	while (dynarr->array[i] != 0)
	{
		newarr[i] = dynarr->array[i];
		i++;
	}
	temp = dynarr->array;
	dynarr->array = newarr;
	free(temp);
	dynarr->capacity = new_capacity;
}

int	add_to_dynamic_int_array(t_dynint *dynarr, int value)
{
	if (dynarr->size == dynarr->capacity)
		expand_dynamic_int_array(dynarr);
	else if (dynarr->size > dynarr->capacity)
		exit(1);
	dynarr->array[dynarr->size] = value;
	dynarr->size += 1;
	return (1);
}