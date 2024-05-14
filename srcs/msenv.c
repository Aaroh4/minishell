/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:54:02 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/14 16:21:07 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Still missing check for heredoc and single/double quotes
char	*move_ucase(char *start)
{
	char	*ptr;

	ptr = start;
	while ((*ptr >= 65 && *ptr <= 90) || *ptr == 95 || *ptr == 63)
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
		ft_memcpy(ms_envp[i], envp[i], slen * sizeof(char));
		ms_envp[i][slen] = '\0';
		i++;
	}
	ms_envp[len] = NULL;
	return (ms_envp);
}

// bs func fix
void	add_to_shell_level(t_shell *sh)
{
	char	*level;
	char	*new_level;

	level = get_env_val("SHLVL", sh);
	if (level == NULL)
	{
		new_level = ft_strdup("1");
		if (new_level == NULL)
			errexit("minishell: ", "malloc error", NULL, sh);
		set_env_var("SHLVL", new_level, sh);
		free(new_level);
	}
	else
	{
		new_level = ft_itoa(ft_atoi(level) + 1);
		if (new_level == NULL)
			errexit("minishell: ", "malloc error", NULL, sh);
		set_env_var("SHLVL", new_level, sh);
		free(new_level);
	}
	free(level);
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

void	populate_env_vars(t_cmdn *node, t_shell *sh)
{
	int	i;

	i = 0;
	while (node->cargs[i] != NULL)
	{
		node->cargs[i] = replace_envp(node->cargs[i], sh);
		i++;
	}
	return ;
}
