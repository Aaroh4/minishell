/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:54:02 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/29 11:37:01 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*move_to_env_end(char *start)
{
	char	*ptr;

	ptr = start;
	while (ft_isalnum(*ptr) || *ptr == 95 || *ptr == 63)
		ptr++;
	return (ptr);
}

char	**copy_env_vals(int len, char **envp, char **ms_envp, t_shell *sh)
{
	int	i;
	int	slen;

	i = 0;
	while (i < len)
	{
		slen = ft_strlen(envp[i]);
		ms_envp[i] = (char *)malloc((slen + 1) * sizeof(char));
		if (ms_envp[i] == NULL)
			errexit("minishell: ", "envp malloc 2 error", NULL, sh);
		ft_memcpy(ms_envp[i], envp[i], (slen + 1) * sizeof(char));
		ms_envp[i][slen] = '\0';
		i++;
	}
	ms_envp[len] = NULL;
	return (ms_envp);
}

char	**copy_envp(char **envp, t_shell *sh)
{
	int		len;
	char	**ms_envp;

	len = 0;
	while (envp[len])
		len++;
	ms_envp = (char **)malloc((len + 1) * sizeof(char *));
	if (ms_envp == NULL)
		errexit("minishell: ", "envp malloc 1 error", NULL, sh);
	copy_env_vals(len, envp, ms_envp, sh);
	return (ms_envp);
}

/*
void	populate_env_vars(t_cmdn *node, t_shell *sh)
{
	int	i;

	i = 0;
	while (node->cargs[i] != NULL)
	{
		node->cargs[i] = replace_envp_tags(node->cargs[i], sh);
		i++;
	}
	return ;
}
*/