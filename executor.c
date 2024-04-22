/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:23:00 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/22 18:02:45 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	exec_cmd(t_cmdn *node, int pfd[2], char **ms_envp)
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
	printf("%d\n", node->hdocs[0]);
	if (node->hdocs[0] > 0)
	{
		ft_putstr_fd(node->cargs[1], pfd[1]);
		node->cargs[1] = NULL;
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
		if (!node->cargs[0] || !*node->cargs || !cmdp
			|| execve(cmdp, node->cargs, ms_envp) == -1)
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
static int	exec_node(t_cmdn *node, int *pfd, char **ms_envp, t_intvec *commands)
{
	int	pid;

	if (node == NULL)
		return (0);
	exec_node(node->left, pfd, ms_envp, commands);
	if (node->ntype == COMMAND)
	{
		populate_env_vars(node, ms_envp);
		pid = fork();
		if (pid == -1)
		{
			wait_for(commands);
			perror("fork error");
		}
		else if (pid == 0)
			exec_cmd(node, pfd, ms_envp);
		else
		{
			//ft_putstr_fd("Created process ID: ", 2);
			//ft_putnbr_fd(pid, 2);
			//ft_putstr_fd(" Command: ", 2);
			//ft_putendl_fd(node->cargs[0], 2);
			add_to_intvec(commands, pid);
		}
	}
	exec_node(node->right, pfd, ms_envp, commands);
	return (0);
}

int	run_cmds(t_shell *sh)
{
	t_intvec	*commands;

	if (sh->root == NULL)
		return (0);
	commands = create_intvec();
	exec_node(sh->root, sh->pfd, sh->ms_envp, commands);
	close(sh->pfd[0]);
	close(sh->pfd[1]);
	wait_for(commands);
	free_intvec(commands);
	return (0);
}
