/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinshelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:58:30 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/28 13:18:51 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

int	find_amount(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (str[i] == c)
		count++;
	return (count);
}

int	get_cargs_count(t_cmdn *node)
{
	int	i;

	i = 0;
	while (node->cargs[i] != NULL)
		i++;
	return (i - 1);
}

char	**remove_array(t_shell *sh, char **temp_ms)
{
	int		j;
	char	*tempstr;
	char	**temp;

	close (sh->efd[1]);
	if (sh->cmdcount == 1)
	{
		tempstr = get_next_line(sh->efd[0]);
		if (tempstr == NULL)
			return (temp_ms);
		temp = removing_loop(tempstr, temp_ms, &j);
		temp[j] = NULL;
		temp = remove_array(sh, temp);
		free(temp_ms);
		return (temp);
	}
	else
		return (temp_ms);
}

char	**removing_loop(char *tempstr, char **temp_ms, int *j)
{
	char	*str;
	int		k;
	char	**temp;

	temp = NULL;
	str = ft_substr(tempstr, 0, ft_strlen(tempstr) - 1);
	free(tempstr);
	*j = count_array(temp_ms);
	temp = malloc(sizeof(char *) * (*j + 1));
	*j = 0;
	k = 0;
	while (temp_ms[*j] != 0)
	{
		if (ft_strncmp(str, temp_ms[*j], ft_strlen(str)))
			temp[k++] = temp_ms[*j];
		else
			free(temp_ms[*j]);
		*j += 1;
	}
	free(str);
	return (temp);
}
