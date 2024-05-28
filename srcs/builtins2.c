/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:10:13 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/28 11:41:23 by mburakow         ###   ########.fr       */
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

void	put_cwd_fd(char *cwd, t_cmdn *node, t_shell *sh)
{
	cwd = ft_strjoin(cwd, node->cargs[1]);
	if (access(cwd, R_OK) == 0)
		ft_putstr_fd(cwd, sh->efd[1]);
	else
		ft_putstr_fd(node->cargs[1], sh->efd[1]);
}

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
	put_cwd_fd(cwd, node, sh);
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

void	check_builtin(t_cmdn *node, t_shell *sh, char *cwd)
{
	clean_cargs_hdrd(node);
	if (!ft_strncmp("export", node->cargs[0], ft_strlen(node->cargs[0])))
		modify_env(sh, 0, cwd);
	else if (!ft_strncmp("unset", node->cargs[0], ft_strlen(node->cargs[0])))
		sh->ms_envp = unset_remove_from_array(sh, sh->ms_envp);
	else if (!ft_strncmp("cd", node->cargs[0], ft_strlen(node->cargs[0])))
		modify_env(sh, 1, cwd);
	else if (!ft_strncmp("exit", node->cargs[0], ft_strlen(node->cargs[0])))
		exit_in_main(node, sh);
	if (sh->cmdcount > 1)
		switch_pipe_fds(sh);
}
