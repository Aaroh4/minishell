/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:15:11 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/24 15:36:55 by ahamalai         ###   ########.fr       */
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

int	count_j(t_cmdn *n, t_shell *sh, int i, int k)
{
	int	j;

	j = 0;
	while (sh->ms_envp[i][j] == n->cargs[k][j]
			&& sh->ms_envp[i][j] != '=')
		j++;
	return (j);
}

int	unset_builtin(t_cmdn *n, t_shell *sh)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	k = 0;
	while (n->cargs[++k] != NULL)
	{
		i = -1;
		if (ft_strncmp(n->cargs[k], n->cargs[k - 1], ft_strlen(n->cargs[k])))
		{
			while (sh->ms_envp[++i] != 0)
			{
				j = count_j(n, sh, i, k);
				if (n->cargs[k][j] == '\0' && sh->ms_envp[i][j] == '=')
				{
					temp = ft_strjoin(sh->ms_envp[i], "\n");
					ft_putstr_fd(temp, sh->efd[1]);
					free(temp);
				}
			}
		}
	}
	return (1);
}
