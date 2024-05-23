/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:15:11 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/22 13:03:20 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	exit_in_main(t_cmdn *node, t_shell *sh)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (sh->cmdcount == 1)
	{
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
		free_new_prompt(sh);
		free_args(sh->ms_envp);
		exit(j);
	}
}


int	echo_builtin(char **arg)
{
	int	i;

	i = 1;
	if (arg == NULL || arg[i] == NULL)
		return (printf("\n"));
	if (ft_strncmp(arg[i], "-n", 3))
	{
		while (arg[i] != NULL)
		{
			printf("%s", arg[i]);
			if (arg[++i] != NULL)
				printf(" ");
		}
		printf("\n");
	}
	else
	{
		while (arg[i + 1] != NULL)
		{
			printf("%s", arg[i + 1]);
			if (arg[++i + 1] != NULL)
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
	int	j;
	int	epos;

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

int	unset_builtin(t_cmdn *node, t_shell *sh)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	k = 0;
	while (node->cargs[++k] != NULL)
	{
		i = -1;
		while (sh->ms_envp[++i] != 0)
		{
			j = 0;
			while (sh->ms_envp[i][j] == node->cargs[k][j]
				&& sh->ms_envp[i][j] != '=')
				j++;
			if (node->cargs[k][j] == '\0' && sh->ms_envp[i][j] == '=')
			{
				temp = sh->ms_envp[i];
				ft_putstr_fd(temp, sh->efd[1]);
				ft_putstr_fd("\n", sh->efd[1]);
				free(temp);
			}
		}
	}
	return (1);
}
