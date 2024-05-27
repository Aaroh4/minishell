/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intvec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:24:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/15 13:17:44 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_intvec	*create_intvec(t_shell *sh)
{
	t_intvec	*intvec;

	intvec = (t_intvec *)malloc(sizeof(t_intvec));
	if (intvec == NULL)
		errexitcode(" error :", "intvec malloc", 1, sh);
	intvec->array = (int *)ft_calloc(INITIAL_SIZE, sizeof(int));
	if (intvec->array == NULL)
	{
		free(intvec);
		errexitcode(" error :", "intvec create malloc", 1, sh);
	}
	intvec->size = 0;
	intvec->capacity = INITIAL_SIZE;
	return (intvec);
}

void	expand_intvec(t_intvec *intvec, t_shell *sh)
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
		errexitcode(" error :", "intvec expand malloc", 1, sh);
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

int	add_to_intvec(t_intvec *intvec, int value, t_shell *sh)
{
	if (intvec->size == intvec->capacity)
		expand_intvec(intvec, sh);
	else if (intvec->size > intvec->capacity)
		errexitcode(" error :", "intvec add", 1, sh);
	intvec->array[intvec->size] = value;
	intvec->size += 1;
	return (1);
}

void	free_intvec(t_intvec *intvec)
{
	free(intvec->array);
	free(intvec);
}
