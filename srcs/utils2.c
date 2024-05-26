/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:50:59 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/26 09:01:30 by mburakow         ###   ########.fr       */
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

char	*loop_remove_quotepair(char *str, int i, int j)
{
	while (str[j] != '\0')
	{
		str[j] = str[j + 1];
		j++;
	}
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

char	*remove_quote_level(char *str)
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
					return (loop_remove_quotepair(str, i, j));
				j--;
			}
		}
		i++;
	}
	return (str);
}

// This needs to account for quotes
char	**remove_quotes_ex_export(char **cmd)
{
	t_bool	export_flag;
	int		i;
	// int		j;
	// char	q;

	// QUOTES!!
	export_flag = FALSE;
	i = -1;
	while (cmd[++i] != NULL)
	{
		if (!ft_strncmp(cmd[i], "export", ft_strlen(cmd[i])))
			export_flag = TRUE;
		if (export_flag && (cmd[i][0] == '<' || cmd[i][0] == '>'))
			export_flag = FALSE;
		if (!export_flag)
			remove_quote_level(cmd[i]);
	}
	return (cmd);
}

// At the moment accounts only for space characters,
//	are other characters necessary?

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
	if (*curs == '\0')
	{
		str[i] = *curs;
		return (str);
	}
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
	while (arr[i])
	{
		dprintf(2, "[%d] ", i);
		dprintf(2, "%s\n", arr[i++]);
	}
}
