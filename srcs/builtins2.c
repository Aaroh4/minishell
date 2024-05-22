/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:10:13 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/22 13:27:23 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_builtin(t_cmdn *node, t_shell *sh, char	*cwd)
{
	char	*home;

	home = check_for_home(sh);
	if (node->cargs[1] == NULL)
	{
		if (home == NULL)
			errexit("cd: ", "HOME not set", NULL, sh);
		else
			ft_putstr_fd(home, sh->efd[1]);
		return (1);
	}
	if (!ft_strncmp(node->cargs[1], "..", 3))
	{
		if (find_amount(cwd, '/') == 1)
			ft_putstr_fd("/", sh->efd[1]);
		else
			ft_putstr_fd(ft_substr(cwd, 0, ft_strlen(cwd) + 1
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
