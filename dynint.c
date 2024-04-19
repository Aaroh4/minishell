/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:24:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/19 11:50:24 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_intvec*	create_intvec(void) 
{
	t_intvec *dynarr;
	
	dynarr = (t_intvec*)malloc(sizeof(t_intvec));
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

void	expand_intvec(t_intvec *dynarr) 
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

int	add_to_intvec(t_intvec *dynarr, int value)
{
	if (dynarr->size == dynarr->capacity)
		expand_intvec(dynarr);
	else if (dynarr->size > dynarr->capacity)
		exit(1);
	dynarr->array[dynarr->size] = value;
	dynarr->size += 1;
	return (1);
}

void	free_intvec(t_intvec *array)
{
	free(array->array);
	free(array);
}