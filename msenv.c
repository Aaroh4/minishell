/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/12 16:24:15 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

char	**copy_envp(char **envp)
{
	int		len;
	int		slen;
	int		i;
	char	**ms_envp;
	
	len = 0;
	while (envp[len])
		len++;
	ms_envp = (char **)malloc((len + 1) * sizeof(char *));
	ft_putstr_fd("MS_ENVP length: ", 2);
	ft_putnbr_fd(len, 2);
	ft_putchar_fd('\n', 2);
	if (ms_envp == NULL)
	{
		perror("ms_envp malloc error");
		exit (1);
	}
	ms_envp[len] = NULL;
	i = 0;
	while (i < len)
	{
		slen = ft_strlen(envp[i]);
		ms_envp[i] = (char *)malloc((slen + 1) *  sizeof(char));
		if (ms_envp[i] == NULL)
		{
			perror("ms_envp malloc error");
			exit (1);
		}
		ft_memcpy(ms_envp[i], envp[i], slen * sizeof(char));
		ms_envp[i][slen] = '\0';
		i++;
	}
	return (ms_envp);
}

// Parse all node->cargs[1++] and populate $ENV with val if found
void	populate_env_vars(t_cmdn *node, char **ms_envp)
{
	while (node->cargs)
		++(node->cargs);
	while (ms_envp)
		++(ms_envp);
	return ;
}