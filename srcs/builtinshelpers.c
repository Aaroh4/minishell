/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinshelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:58:30 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/22 14:33:25 by ahamalai         ###   ########.fr       */
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

char	*check_for_home(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->ms_envp[i] != 0)
	{
		if (!ft_strncmp(sh->ms_envp[i], "HOME=", 5))
			return (sh->ms_envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**remove_array(t_shell *sh, char **temp_ms)
{
	int		j;
	char	*str;
	char	*tempstr;
	int		k;
	char	**temp;

	close (sh->efd[1]);
	if (sh->cmdcount == 1)
	{
		tempstr = get_next_line(sh->efd[0]);
		if (tempstr == NULL)
			return (temp_ms);
		str = ft_substr(tempstr, 0, ft_strlen(tempstr) - 1);
		free(tempstr);
		j = count_array(temp_ms);
		temp = malloc(sizeof(char *) * (j + 1));
		j = 0;
		k = 0;
		while (temp_ms[j] != 0)
		{
			if (ft_strncmp(str, temp_ms[j], ft_strlen(str)))
				temp[k++] = temp_ms[j];
			else
				free(temp_ms[j]);
			j++;
		}
		temp[j] = NULL;
		temp = remove_array(sh, temp);
		free(temp_ms);
		free(str);
		return (temp);
	}
	else
		return (temp_ms);
}
