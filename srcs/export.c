/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 03:59:37 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/26 12:21:50 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void	export_quote_expand_env(char *val, t_cmdn *node, t_shell *sh)
{
	int		i;
	char	c;
	int		qulvl;

	i = 0;
	c = 0;
	qulvl = 0;
	while (val[i] != '\0')
	{
		if (val[i] == '\"' || val[i] == '\'')
		{
			c = val[i];
			if (test_quote_level(&val[i]))
			{
				if (c == '\"')
				{
					
				}
			}
		}
		i++;
	}
}
*/

int export_check_envname(int j, t_cmdn *node, t_shell *sh)
{
	int i;

	i = 0;
	if ((ft_isalpha(node->cargs[j][0])) || (node->cargs[j][0] == '_'))
	{
		while ((ft_isalnum(node->cargs[j][i])) || (node->cargs[j][i] == '_'))
			i++;
		if (node->cargs[j][i] == '=')
		{
			// export_quote_expand_env(&node->cargs[j][i + 1], node, sh);
			remove_quote_level(&node->cargs[j][i + 1], sh); 
			ft_putstr_fd(node->cargs[j], sh->efd[1]);
			ft_putstr_fd("\n", sh->efd[1]);
			return (i);
		}
		else if (node->cargs[j][i] != '\0')
			errexit("export: \'", node->cargs[j], "\': not a valid identifier", sh);
	}
	else
		errexit("export: \'", node->cargs[j], "\': not a valid identifier", sh);
	return (0);
}

int	export_builtin(t_cmdn *node, t_shell *sh)
{
	int		i;

	print_char_array(node->cargs);
	if (node->cargs[1] == 0)
	{
		env_builtin(sh, TRUE);
		return (1);
	}
	i = 1;
	while (node->cargs[i] != NULL)
	{
		export_check_envname(i, node, sh);
		i++;
	}
	return (1);
}