/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:50:59 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/24 12:06:44 by ahamalai         ###   ########.fr       */
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

// Breaks export, we need to handle export ABC="a b c"
// So that env: ABC=a b c 
char	**remove_quotes_ex_export(char **cmd)
{
	t_bool	export_flag;
	int		i;
	int		j;

	export_flag = FALSE;
	i = -1;
	while (cmd[++i] != NULL)
	{
		j = 0;
		if (!ft_strncmp(cmd[i], "export", ft_strlen(cmd[i])))
			export_flag = TRUE;
		if (export_flag && (cmd[i][0] == '<' || cmd[i][0] == '>'))
			export_flag = FALSE;
		if (!export_flag)
		{
			while (cmd[i][j] != '\0')
			{
				if (cmd[i][j] == '\"' || cmd[i][j] == '\'')
				{
					while (cmd[i][j] != '\0')
					{
						cmd[i][j] = cmd[i][j + 1];
						j++;
					}
					j = 0;
				}
				else
					j++;
			}
		}
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

void	print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		dprintf(2, "%s\n", arr[i++]);
}
