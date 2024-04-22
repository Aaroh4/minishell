/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:54:02 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/22 17:17:37 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	**copy_env_vals(int len, char **envp, char **ms_envp)
{
	int	i;
	int	slen;

	i = 0;
	while (i < len)
	{
		slen = ft_strlen(envp[i]);
		ms_envp[i] = (char *)malloc((slen + 1) * sizeof(char));
		if (ms_envp[i] == NULL)
		{
			perror("ms_envp malloc 2 error");
			exit(1);
		}
		ft_memcpy(ms_envp[i], envp[i], slen * sizeof(char));
		ms_envp[i][slen] = '\0';
		i++;
	}
	ms_envp[len] = NULL;
	return (ms_envp);
}

char	**copy_envp(char **envp)
{
	int		len;
	char	**ms_envp;

	len = 0;
	while (envp[len])
		len++;
	ms_envp = (char **)malloc((len + 1) * sizeof(char *));
	if (ms_envp == NULL)
	{
		perror("ms_envp malloc error");
		exit(1);
	}
	copy_env_vals(len, envp, ms_envp);
	return (ms_envp);
}

void	populate_env_vars(t_cmdn *node, char **ms_envp)
{
	int	i;

	i = 0;
	while (node->cargs[i] != NULL)
	{
		node->cargs[i] = replace_envp(node->cargs[i], ms_envp);
		i++;
	}
	return ;
}
