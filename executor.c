/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:23:00 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/12 15:45:27 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	exec_cmd(t_cmdn *node, int pfd[2])
{
	char	**path_array;
	char	*cmdp;
	char	*cwd;

	if (dup2(pfd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 stdin error");
		exit(EXIT_FAILURE);
	}
	close(pfd[0]);
	if (node->last == FALSE)
	{
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout error");
			exit(EXIT_FAILURE);
		}
	}
	close(pfd[1]);
	cwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd error");
		exit(EXIT_FAILURE);
	}
	if (!ft_strncmp(node->cargs[0], "pwd", 4))
		pwd_builtin();
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "cd", 3))
		cd_builtin(cwd, node->cargs);
	else if (node->cargs[0] && !ft_strncmp(node->cargs[0], "echo", 5))
		echo_builtin(node->cargs);
	else
	{
		path_array = ft_split(getenv("PATH"), ":");
		cmdp = get_exec_path(path_array, node->cargs[0]);
		free(path_array);
		if (cmdp == NULL)
			exit (127);
		if (!node->cargs[0] || !*node->cargs || !cmdp
			|| execve(cmdp, node->cargs, NULL) == -1)
		{
			printf("Execve error.\n");
			exit (127);
		}
	}
	free(cwd);
	exit (EXIT_SUCCESS);
}

// If node->right type command it's last so rockit
// Might not work with bonuses though
static int	exec_node(t_cmdn *node, int *pfd, char **ms_envp, t_dynint *commands)
{
	int	pid;

	if (node == NULL)
		return (0);
	exec_node(node->left, pfd, ms_envp, commands);
	if (node->ntype == COMMAND)
	{
		// populate_env_vars(node, ms_envp);
		pid = fork();
		if (pid == -1)
		{
			wait_for(commands);
			perror("fork error");
		}
		else if (pid == 0)
			exec_cmd(node, pfd);
		else
		{
			//ft_putstr_fd("Created process ID: ", 2);
			//ft_putnbr_fd(pid, 2);
			//ft_putstr_fd(" Command: ", 2);
			//ft_putendl_fd(node->cargs[0], 2);
			add_to_dynamic_int_array(commands, pid);
		}
	}
	exec_node(node->right, pfd, ms_envp, commands);
	return (0);
}

int	run_cmds(t_cmdn *root, int *pfd, char **ms_envp)
{
	t_dynint	*commands;

	if (root == NULL)
		return (0);
	commands = create_dynamic_int_array();
	exec_node(root, pfd, ms_envp, commands);
	close(pfd[0]);
	close(pfd[1]);
	wait_for(commands);
	return (0);
}
