/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:15:11 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/10 10:55:54 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
			write(1, "No home\n", 8);
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
			write(1, "NUM\n", 4); // PUT THE NUM FROM CARGS TO THE STATUS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! //
		else
			printf("exit: %s: numeric argument required\n", node->cargs[1]);
	}
	if (sh->cmdarr[1] == NULL)
	{
		free_new_prompt(sh);
		free_args(sh->ms_envp);
		exit(0);
	}
	free_new_prompt(sh);
	free_args(sh->ms_envp);
}

//int	exit_builtin(t_cmdn *node, t_shell *sh)
//{
//	if (node->cargs != NULL)
//		ft_putstr_fd(node->cargs[1], sh->efd[1]);
//	return (1);
//}

int	echo_builtin(char **arg)
{
	int	i;

	i = 1;
	if (ft_strncmp(arg[i], "-n", 3))
	{
		while (arg[i] != NULL)
		{
			printf("%s", arg[i++]);
			if (arg[i] != NULL)
				printf("%s", " ");
		}
		printf("\n");
	}
	else
	{
		i++;
		while (arg[i] != NULL)
		{
			printf("%s", arg[i++]);
			if (arg[i] != NULL)
				printf("%s", " ");
		}
	}
	return (1);
}

int	export_builtin(t_cmdn *node, t_shell *sh)
{
	int		i;

	i = 0;
	if (node->cargs[1] == 0)
	{
		env_builtin(sh, TRUE);
		return (1);
	}
	i = 0;
	if ((node->cargs[1][0] >= 'a' && node->cargs[1][0] <= 'z')
		|| (node->cargs[1][0] >= 'A' && node->cargs[1][0] <= 'Z')
		|| (node->cargs[1][0] == '_'))
	{
		while ((node->cargs[1][i] >= 'a' && node->cargs[1][i] <= 'z')
			|| (node->cargs[1][i] >= 'A' && node->cargs[1][i] <= 'Z')
			|| (node->cargs[1][i] >= '0' && node->cargs[1][i] <= '9')
			|| (node->cargs[1][i] == '_'))
			i++;
		if (node->cargs[1][i] == '=')
			ft_putstr_fd(node->cargs[1], sh->efd[1]);
	}
	else
		errexit("export: '", node->cargs[1], "': not a valid identifier", sh);
	// "': not a valid identifier"
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

char	**remove_array(t_shell *sh)
{
	int		j;
	int		i;
	int		k;
	char	**temp;

	j = 0;
	close (sh->efd[1]);
	i = ft_atoi(get_next_line(sh->efd[0]));
	if (i == -1)
		return (sh->ms_envp);
	while (sh->ms_envp[j] != 0)
		j++;
	temp = db_malloc(sizeof(char *) * (j));
	j = 0;
	k = 0;
	while (sh->ms_envp[j] != 0)
	{
		if (j != i)
			temp[k++] = sh->ms_envp[j];
		j++;
	}
	temp[j] = NULL;
	return (temp);
}

int	unset_builtin(t_cmdn *node, t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (sh->ms_envp[i] != 0)
	{
		j = 0;
		while (sh->ms_envp[i][j] == node->cargs[1][j] && sh->ms_envp[i][j] != '=')
			j++;
		if (node->cargs[1][j] == '\0')
		{
			// THIS LEAKS!!!
			ft_putstr_fd(ft_itoa(i), sh->efd[1]);
			break ;
		}
		i++;
	}
	if (j == 0)
		ft_putstr_fd("-1", sh->efd[1]);
	return (1);
}
