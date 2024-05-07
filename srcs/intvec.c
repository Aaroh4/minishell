/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:24:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/07 13:21:18 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_intvec	*create_intvec(void)
{
	t_intvec	*intvec;

	intvec = (t_intvec *)malloc(sizeof(t_intvec));
	if (intvec == NULL)
		exit(1);
	intvec->array = (int *)ft_calloc(INITIAL_SIZE, sizeof(int));
	if (intvec->array == NULL)
	{
		free(intvec);
		exit(1);
	}
	intvec->size = 0;
	intvec->capacity = INITIAL_SIZE;
	return (intvec);
}

void	expand_intvec(t_intvec *intvec)
{
	size_t	new_capacity;
	int		*newarr;
	int		*temp;
	int		i;

	new_capacity = intvec->capacity * 2;
	newarr = (int *)ft_calloc(new_capacity, sizeof(int));
	if (newarr == NULL)
	{
		free(intvec->array);
		free(intvec);
		exit(1);
	}
	i = 0;
	while (intvec->array[i] != 0)
	{
		newarr[i] = intvec->array[i];
		i++;
	}
	temp = intvec->array;
	intvec->array = newarr;
	free(temp);
	intvec->capacity = new_capacity;
}

int	add_to_intvec(t_intvec *intvec, int value)
{
	if (intvec->size == intvec->capacity)
		expand_intvec(intvec);
	else if (intvec->size > intvec->capacity)
		exit(1);
	intvec->array[intvec->size] = value;
	intvec->size += 1;
	return (1);
}

void	free_intvec(t_intvec *intvec)
{
	free(intvec->array);
	free(intvec);
}
