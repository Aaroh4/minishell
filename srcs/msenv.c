/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:54:02 by mburakow          #+#    #+#             */
/*   Updated: 2024/06/04 15:54:55 by mburakow         ###   ########.fr       */
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
		if (ms_envp[i][0] == '_')
			ms_envp[i][ft_strcpos(ms_envp[i], '.')] = '\0';
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
