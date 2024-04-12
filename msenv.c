/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/12 19:11:00 by mburakow         ###   ########.fr       */
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
	// ft_putstr_fd("MS_ENVP length: ", 2);
	// ft_putnbr_fd(len, 2);
	// ft_putchar_fd('\n', 2);
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
			perror("ms_envp malloc 2 error");
			exit (1);
		}
		ft_memcpy(ms_envp[i], envp[i], slen * sizeof(char));
		ms_envp[i][slen] = '\0';
		i++;
	}
	return (ms_envp);
}

char	*exp_env(char *arg, int j, char **ms_envp)
{
	int		len;
	int		i;
	char	*test_env;
	char	*expd_env;
	char	*tmp;

	len = 0;
	while (arg[j + len] != 32)
		len++;
	test_env = ft_substr(arg, j, len);
	if (test_env == NULL)
	{
		perror("test_env malloc error");
		exit (1);
	}
	i = 0;
	expd_env = NULL;
	while (ms_envp[i] != NULL)
	{
		if (!ft_strncmp(ms_envp[i], test_env, ft_strlen(test_env)))
			expd_env = ms_envp[i];
		i++;
	}
	tmp = ft_strjoin
	// To be continued...
}

// Parse all node->cargs[1++] and populate $ENV with val if found. Also $?.
// If it's from heredoc, always expand.
// If it's from parameter array, expand when inside 
void	populate_env_vars(t_cmdn *node, char **ms_envp)
{
	int		i;
	int		j;

	i = 0;
	while (node->cargs[i] != NULL)
	{
		j = 0;
		while (node->cargs[i][j] != '\0')
		{
			if (node->cargs[i][j] == 36)
				node->cargs[i] = exp_env(node->cargs[i], j, ms_envp);
		}
		i++;
	}
	return ;
}