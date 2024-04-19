/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msenv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 13:16:33 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/19 11:26:29 by mburakow         ###   ########.fr       */
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

char	*get_env_end(char *env, char **ms_envp)
{
	int		i;
	char	*env_val;

	i = 0;
	env_val = "";
	while (ms_envp[i] != NULL)
	{
		if (!strncmp(ms_envp[i], env, ft_strlen(env)))
		{
			env_val = ft_strchr(ms_envp[i], 61) + 1;
			break;
		}
		i++;
	}
	return (env_val);
}

char	*move_ucase(char *start)
{
	char	*ptr;

	ptr = start;
	while ((*ptr >= 65 && *ptr <= 90) || *ptr == 95)
		ptr++;
	return (ptr);
}

char *replace_envp(char* input, char **ms_envp, int hdoc)
{
	char	*start;
	char 	*end;
	char	*new_arr;
	char 	*env_val;
	char 	*temp;
	int		i;
	int		total_len;

	// hdoc not yet implemented
	hdoc = 0;
	i = hdoc;
	start = input;
	while ((start = ft_strchr(start, 36)) != NULL)
	{
		end = move_ucase(start + 1);
		env_val = "";
		i = 0;
		while (ms_envp[i] != NULL) 
		{
            if (!ft_strncmp(ms_envp[i], start + 1, ft_strcpos(ms_envp[i], 61))) 
			{
                env_val = ft_strchr(ms_envp[i], 61) + 1;
				end = start + ft_strcpos(ms_envp[i], 61) + 1;
                break;
            }
            i++;
        }
		total_len = ft_strlen(input) - ft_strlen(start) + ft_strlen(env_val) + ft_strlen(end);
		new_arr = (char *)malloc((total_len + 1) * sizeof(char));
		if (new_arr == NULL)
		{
			perror("ms_envp malloc 3 error");
			exit (1);
		}
		i = 0;
		temp = input;
		while (temp != start)
		{
			new_arr[i] = *temp;
			temp++;
			i++;
		}
		while (*env_val != '\0')
		{
			new_arr[i] = *env_val;
			i++;
			env_val++;
		}
		start = new_arr + i; 
		while (*end != '\0')
		{
			new_arr[i] = *end;
			i++;
			end++;
		}
		new_arr[ft_strlen(new_arr)] = '\0';
		free(input);
		input = new_arr;
	}
	return (input);
}

void	populate_env_vars(t_cmdn *node, char **ms_envp)
{
	int		i;

	i = 0;
	while (node->cargs[i] != NULL)
	{
		node->cargs[i] = replace_envp(node->cargs[i], ms_envp, node->hdocs[i]);
		i++;
	}
	return ;
}

/*
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

int	add_expd_to_arg(char *expd_arg, char *expd_env, char *arg, int j)
{
	//char	*tmp;

	// tmp = ft_strjoin(expd_arg, NULL);
	return (0);
}

char	*exp_env(char *arg, char **ms_envp)
{
	int		j;
	char	*expd_arg;
	char	*test_env;
	char	*expd_env;

	expd_arg = NULL;
	j = 0;
	while (arg[j] != '\0')
	{
		if (arg[j] == 36)
		{
			// Find the string after $
			test_env = find_test_env(arg, j);
			// Test if corresponding env var is found
			expd_env = check_test_env(test_env, ms_envp);
			free(test_env);
			// If it is found, add stuff after previous $ and expd_env to expd_arg
			if (expd_env != NULL)
				j = add_expd_to_arg(expd_arg, expd_env, arg, j);
		}
		j++;
	}
	return (expd_arg);
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
*/