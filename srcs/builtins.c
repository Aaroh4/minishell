/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:15:11 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/20 15:08:56 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	get_cargs_count(t_cmdn *node)
{
	int	i;

	i = 0;
	while (node->cargs[i] != NULL)
		i++;
	return (i - 1);
}

char	*check_for_home(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->ms_envp[i] != 0)
	{
		if (!ft_strncmp(sh->ms_envp[i], "HOME=", 5))
			return (sh->ms_envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	find_amount(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (str[i] == c)
		count++;
	return (count);
}

int	cd_builtin(t_cmdn *node, t_shell *sh, char	*cwd)
{
	char	*home;

	home = check_for_home(sh);
	if (node->cargs[1] == NULL)
	{
		if (home == NULL)
			write(1, "cd: HOME not set\n", 17);
		else
			ft_putstr_fd(home, sh->efd[1]);
		return (1);
	}
	if (!ft_strncmp(node->cargs[1], "..", 3))
	{
		if (find_amount(cwd, '/') == 1)
			ft_putstr_fd("/", sh->efd[1]);
		else
			ft_putstr_fd(ft_substr(cwd, 0, ft_strlen(cwd)
					- ft_strlen(ft_strrchr(cwd, '/'))), sh->efd[1]);
		return (1);
	}
	if (node->cargs[1][0] != '/' && access(ft_strjoin(cwd, "/"), R_OK) == 0)
		cwd = ft_strjoin(cwd, "/");
	cwd = ft_strjoin(cwd, node->cargs[1]);
	if (access(cwd, R_OK) == 0)
		ft_putstr_fd(cwd, sh->efd[1]);
	else
		ft_putstr_fd(node->cargs[1], sh->efd[1]);
	return (1);
}

int	pwd_builtin(t_shell *sh)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		errexit("pwd:", "getcwd error", NULL, sh);
	return (1);
}

void	exit_in_main(t_cmdn *node, t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (sh->cmdarr[1] == NULL)
		write(1, "exit\n", 5);
	if (node->cargs[1] != NULL && node->hdocs[1] == 0)
	{
		while (node->cargs[1][i] != '\0')
			i++;
		while (ft_isdigit(node->cargs[1][j]) && node->cargs[1][j] != '\0')
			j++;
		if (j == i)
			j = ft_atoi(node->cargs[1]);
		else
			printf("exit: %s: numeric argument required\n", node->cargs[1]);
	}
	if (sh->cmdarr[1] == NULL)
	{
		free_new_prompt(sh);
		free_args(sh->ms_envp);
		exit(j);
	}
	free_new_prompt(sh);
	free_args(sh->ms_envp);
}


int	echo_builtin(char **arg)
{
	int	i;

	i = 1;
	if (arg == NULL || arg[i] == NULL)
		return (1);
	if (ft_strncmp(arg[i], "-n", 3))
	{
		while (arg[i] != NULL)
		{
			printf("%s", arg[i]);
			if (arg[i + 1] != NULL)
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else
	{
		i++;
		while (arg[i] != NULL)
		{
			printf("%s", arg[i]);
			if (arg[++i] != NULL)
				printf("%s", " ");
		}
	}
	return (1);
}

int	export_builtin(t_cmdn *node, t_shell *sh)
{
	int		i;
	int		j;

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
			}
			else if (node->cargs[j][i] != '\0')
				printf("export: \'%s\': not a valid identifier\n", node->cargs[j]);
		}
		else
			printf("export: \'%s\': not a valid identifier\n", node->cargs[j]);
	}
	return (1);
}

int	env_builtin(t_shell *sh, t_bool export)
{
	int	i;
	int j;
	int epos;

	i = 0;
	while (sh->ms_envp[i] != 0)
	{
		j = 0;
		if (export)
		{
			epos = ft_strcpos(sh->ms_envp[i], '=');
			ft_putstr_fd("declare -x ", 1);
			while (j <= epos)
				ft_putchar_fd(sh->ms_envp[i][j++], 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(&sh->ms_envp[i][j], 1);
			ft_putendl_fd("\"", 1);
		}
		else
			printf("%s\n", sh->ms_envp[i]);
		i++;
	}
	return (1);
}

int	count_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		i++;
	return (i);
}

char	**remove_array(t_shell *sh, char **temp_ms)
{
	int		j;
	char	*str;
	char	*tempstr;
	int		k;
	char	**temp;

	close (sh->efd[1]);
	tempstr = get_next_line(sh->efd[0]);
	if (tempstr == NULL)
		return (temp_ms);
	str = ft_substr(tempstr, 0, ft_strlen(tempstr) - 1);
	free(tempstr);
	j = count_array(temp_ms);
	temp = malloc(sizeof(char *) * (j + 1));
	j = 0;
	k = 0;
	while (temp_ms[j] != 0)
	{
		if (ft_strncmp(str, temp_ms[j], ft_strlen(str)))
			temp[k++] = temp_ms[j];
		else
			free(temp_ms[j]);
		j++;
	}
	temp[j] = NULL;
	temp = remove_array(sh, temp);
	free(temp_ms);
	free(str);
	return (temp);
}

int	unset_builtin(t_cmdn *node, t_shell *sh)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = 0;
	k = 0;
	while (node->cargs[++k] != NULL)
	{
		i = 0;
		while (sh->ms_envp[i] != 0)
		{
			j = 0;
			while (sh->ms_envp[i][j] == node->cargs[k][j] && sh->ms_envp[i][j] != '=')
				j++;
			if (node->cargs[k][j] == '\0' && sh->ms_envp[i][j] == '=')
			{
			//	printf("%s\n", node->cargs[k]);
				temp = sh->ms_envp[i];
				ft_putstr_fd(temp, sh->efd[1]);
				ft_putstr_fd("\n", sh->efd[1]);
				free(temp);
			}
			i++;
		}
	}
	//if (j == 0)
	//	ft_putstr_fd("-1", sh->efd[1]);
	return (1);
}
