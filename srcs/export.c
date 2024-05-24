/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 03:59:37 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/24 13:30:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_builtin(t_cmdn *node, t_shell *sh)
{
	int		i;
	int		j;

	print_char_array(node->cargs);
	if (node->cargs[1] == 0)
	{
		env_builtin(sh, TRUE);
		return (1);
	}
	j = 0;
	while (node->cargs[++j] != NULL)
	{
		i = 0;
		if ((ft_isalpha(node->cargs[j][0])) || (node->cargs[j][0] == '_'))
		{
			while ((ft_isalnum(node->cargs[j][i])) || (node->cargs[j][i] == '_'))
				i++;
			if (node->cargs[j][i] == '=')
			{
				ft_putstr_fd(node->cargs[j], sh->efd[1]);
				ft_putstr_fd("\n", sh->efd[1]);
				return (1);
			}
			else if (node->cargs[j][i] != '\0')
				errexit("export: \'", node->cargs[j], "\': not a valid identifier", sh);
		}
		else
			errexit("export: \'", node->cargs[j], "\': not a valid identifier", sh);
	}
	return (1);
}