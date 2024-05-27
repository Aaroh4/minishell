/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:08:31 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/27 22:10:50 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdn(t_cmdn *node)
{
	int	i;

	if (node == NULL)
		return ;
	print_cmdn(node->left);
	i = 0;
	if (node->ntype == COMMAND)
		ft_putendl_fd("COMMAND:", 2);
	if (node->ntype == PIPELINE)
		ft_putendl_fd("PIPELINE:", 2);
	while (node->cargs && node->cargs[i] != 0)
	{
		if (i != 0)
			ft_putchar_fd('\t', 2);
		ft_putendl_fd(node->cargs[i], 2);
		i++;
	}
	ft_putnbr_fd(node->last, 2);
	ft_putchar_fd('\n', 2);
	print_cmdn(node->right);
}

// ATM accounts only for spaces
char	*trim_string(char *str)
{
	int		i;
	char	*end;
	char	*curs;

	i = 0;
	if (!str || str[0] == '\0' || str[0] == 0)
		return (str);
	while ((unsigned char)str[i] == 32)
		i++;
	curs = &str[i];
	i = 0;
	while (*curs != '\0')
	{
		str[i++] = *curs;
		curs++;
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && (unsigned char)*end == 32)
		end--;
	end[1] = '\0';
	return (str);
}

void	print_char_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		dprintf(2, "[%d] ", i);
		dprintf(2, "%s\n", arr[i++]);
	}
}

char	test_quote_level(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			j = ft_strlen(str) - 1;
			while (j > i)
			{
				if (str[j] == str[i])
					return (str[i]);
				j--;
			}
		}
		i++;
	}
	return (-1);
}

int	skip_quotes(char *str, int i)
{
	int q;

	if (str[i] == '\"' || str[i] == '\'')
	{
		q = i + 1;
		while (str[q] != '\0')
		{
			if (str[q] == str[i])
				return (q);
			q++;
		}
	}
	return (i);
}