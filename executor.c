/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:23:00 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/25 15:21:15 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// Path is checked every time from ms_envp since it could have been changed
// in previous pipe.
static int	exec_builtin(t_cmdn *node, char *cwd, t_shell *sh)
{
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		errexit("error:", "getcwd", sh, 1);
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "echo", 5))
		return (echo_builtin(node->cargs));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "cd", 3))
		return (cd_builtin(cwd, node->cargs));
	if (node->cargs[0] && !ft_strncmp(node->cargs[0], "pwd", 4))
		return (pwd_builtin());
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "export", 7))
		return (export_builtin(node, sh));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "unset", 6))
		return (unset_builtin(node, sh));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "env", 4))
		return (env_builtin(sh));
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "exit", 5))
		exit_builtin(sh);
	else
		return (0);
}

static void	exec_cmd(t_cmdn *node, t_shell *sh)
{
	char	**path_array;
	char	*cmdp;
	char	*cwd;

	if (dup2(sh->pfd[0], STDIN_FILENO) == -1)
		errexit("error:", "dup2 stdin", sh, 127);
	close(sh->pfd[0]);
	if (node->last == FALSE && dup2(sh->pfd[1], STDOUT_FILENO) == -1)
		errexit("error:", "dup2 stdout", sh, 127);
	close(sh->pfd[1]);
	cwd = NULL;
	if (!exec_builtin(node, cwd, sh))
	{
		path_array = ft_split(getenv("PATH"), ":");
		cmdp = get_exec_path(path_array, node->cargs[0]);
		free(path_array);
		if (!node->cargs[0] || !*node->cargs || !cmdp || execve(cmdp,
				node->cargs, sh->ms_envp) == -1)
		{
			free(cwd);
			errexit("error:", "execve", sh, 127);
		}
	}
	free(cwd);
	exit(EXIT_SUCCESS);
}

// If node->right type command it's last so rockit
// Might not work with bonuses though
static int	exec_node(t_cmdn *node, t_shell *sh, t_intvec *commands)
{
	int	pid;

	if (node == NULL)
		return (0);
	exec_node(node->left, sh, commands);
	if (node->ntype == COMMAND)
	{
		populate_env_vars(node, sh);
		pid = fork();
		if (pid == -1)
		{
			sh->status = wait_for(commands);
			free_intvec(commands);
			errexit("Error:", "fork failure", sh, 1);
		}
		else if (pid == 0)
			exec_cmd(node, sh);
		else
			add_to_intvec(commands, pid);
	}
	exec_node(node->right, sh, commands);
	return (0);
}

int	run_cmds(t_shell *sh)
{
	t_intvec	*commands;

	if (sh->root == NULL)
		return (0);
	commands = create_intvec();
	exec_node(sh->root, sh, commands);
	close(sh->pfd[0]);
	close(sh->pfd[1]);
	sh->status = wait_for(commands);
	free_intvec(commands);
	return (0);
}
