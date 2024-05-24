/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:50:59 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/24 11:24:17 by mburakow         ###   ########.fr       */
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
	char	**cmdi;
	char	*cur;
	t_bool	export_flag;
	int		i;

	cmdi = cmd;
	export_flag = FALSE;
	while (*cmdi != NULL)
	{
		cur = *cmdi;
		if (!ft_strncmp(cur, "export", ft_strlen(cur)))
			export_flag = TRUE;
		if (export_flag && (cur[0] =='<' || cur[0] == '>'))
			export_flag = FALSE;
		// dprintf(2, "cur is: %s\n", cur);
		if (!export_flag)
		{
			while (*cur != '\0')
			{
				if (*cur == '\"')
				{
					i = 0;
					while (cur[i + 1] != '\0')
					{
						cur[i] = cur[i + 1];
						i++;
					}
					cur[i] = '\0';
				}
				cur++;
			}
		}
		cmdi++;
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
		dprintf(2, "%s\n", arr[i++]);
}
