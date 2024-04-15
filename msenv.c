/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/15 15:24:38 by mburakow         ###   ########.fr       */
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

// mallocs needs free
char	*find_test_env(char *arg, int j)
{
	size_t	len;
	char	*test_env;

	len = 0;
	while (arg[j + len] != 32 && arg[j + len] != '\0')
		len++;
	test_env = ft_substr(arg, (j + 1), len);
	if (test_env == NULL)
	{
		perror("test_env malloc error");
		exit (1);
	}
	printf("Found test env: %s\n", test_env);
	return (test_env);
}

char	*check_test_env(char *test_env, char **ms_envp)
{
	int		i;
	char 	*expd_env;
	
	i = 0;
	while (ms_envp[i] != NULL)
	{
		if (!ft_strncmp(ms_envp[i], test_env, ft_strlen(test_env)))
			expd_env = ft_substr(ms_envp[i], (ft_strlen(test_env) + 1), 
				ft_strlen(ms_envp[1]));
		i++;
	}
	if (expd_env != NULL)
	{
		printf("Expanded env to: %s\n", expd_env);
	}
	return (expd_env);
}

char	*exp_env(char *arg, char **ms_envp)
{
	int		len;
	int		j;
	int		i;
	char	*expd_arg;
	char	*test_env;
	char	*expd_env;

	expd_arg = NULL;
	j = 0;
	len = 0;
	while (arg[j] != '\0')
	{
		if (arg[j] == 36)
		{
			test_env = find_test_env(arg, j);
			expd_env = check_test_env(test_env, ms_envp);
			i = 0;
			while (ms_envp[i] != NULL)
			{
				if (!ft_strncmp(ms_envp[i], test_env, ft_strlen(test_env)))
					expd_env = ft_substr(ms_envp[i], (ft_strlen(test_env) + 1), 
						ft_strlen(ms_envp[1]));
				i++;
			}
			if (expd_env != NULL)
			{
				printf("Expanded env to: %s\n", expd_env);
			}
		}
		j++;
	}
	return (expd_env);
}


// Parse all node->cargs[1++] and populate $ENV with val if found. Also $?.
// If it's from heredoc, always expand.
// If it's from parameter array, expand when inside 
void	populate_env_vars(t_cmdn *node, char **ms_envp)
{
	int		i;
	int		j;
	char	*expd_arg;

	i = 1;
	while (node->cargs[i] != NULL)
	{
		j = 0;
		while (node->cargs[i][j] != '\0')
		{
			// Here account for single quotes! Found dollar sign:
			if (node->cargs[i][j] == 36)
			{
				expd_arg = exp_env(node->cargs[i], ms_envp);
				if (expd_arg != NULL)
				{
					free (node->cargs[i]);
					node->cargs[i] = expd_arg;
				}
				break ;
			}
			j++;
		}
		i++;
	}
	return ;
}