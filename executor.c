/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:23:00 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/11 18:02:24 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

static void	exec_cmd(t_cmdn *node, int pfd[2], t_bool last)
{
	char	**path_array;
	char	*cmdp;
	char	*cwd;

	if (dup2(pfd[0], STDIN_FILENO) == -1)
		perror("dup2 stdin error");
	close(pfd[0]);
	if (last == FALSE)
	{
		if (dup2(pfd[1], STDOUT_FILENO) == -1)
			perror("dup2 stdout error");
	}
	close(pfd[1]);
	cwd = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd error");
	if (!ft_strncmp(node->cargs[0], "pwd", 4))
		pwd_builtin();
	else if (node->cargs[0] != '\0' && !ft_strncmp(node->cargs[0], "cd", 3))
		cd_builtin(cwd, node->cargs);
	else if (node->cargs[0] != '\0' && !ft_strncmp(node->cargs[0], "echo", 5))
		echo_builtin(node->cargs);
	else
	{
		path_array = ft_split(getenv("PATH"), ":");
		cmdp = get_exec_path(path_array, node->cargs[0]);
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
	//close(pfd[0]);
	//close(pfd[1]);
	exit (0);
}

// If node->right type command it's last so rockit
// Might not work with bonuses though
static int	exec_node(t_cmdn *node, int *pfd, t_dynint *commands, t_bool last)
{
	int	pid;

	if (node == NULL)
		return (0);
	exec_node(node->left, pfd, commands, FALSE);
	if (node->ntype == COMMAND)
	{
		pid = fork();
		if (pid == -1)
		{
			wait_for(commands);
			perror("fork error");
		}
		else if (pid == 0)
			exec_cmd(node, pfd, last);
		else
			add_to_dynamic_int_array(commands, pid);
	}
	if (node->right && node->right->ntype == COMMAND)
		exec_node(node->right, pfd, commands, TRUE);
	else
		exec_node(node->right, pfd, commands, FALSE);
	return (0);
}

int	run_cmds(t_cmdn *root)
{
	int			pfd[2];
	t_dynint	*commands;
	
	if (root == NULL)
		return (0);
	if (pipe(pfd) == -1)
	{
		free_cmdn(root);
		perror("pipe init error.");
	}
	commands = create_dynamic_int_array();
	exec_node(root, pfd, commands, FALSE);
	wait_for(commands);
	close(pfd[0]);
	close(pfd[1]);
	return (0);
}

/*
void	print_cmdn(t_cmdn *node)
{
	int	i;

	if (node == NULL)
		return ;
	print_cmdn(node->left);
	i = 0;
	while (node->cargs && node->cargs[i] != '\0')
	{
		if (i != 0)
			printf("\t");
		printf("%s\n", node->cargs[i]);
		i++;
	}
	print_cmdn(node->right);
}

static	add_to_commands(int pid, int **commands)
{
	static int	i = 0;

	if (commands == NULL)
	{
		commands = ft_calloc(5, sizeof(int *));
		commands[0] = pid;
	}
	else  
	{

	}

}

static int	exec_node(t_cmdn *node, int *pfd, int **commands)
{
	int	pid;
	int status;

	if (node == NULL)
		return (0);
	exec_node(node->left, pfd, commands);
	if (node->ntype == COMMAND)
	{
		pid = fork();
		if (pid == -1)
		{
			wait_for(commands);
			exit (1);
		}
		else if (pid == 0)
			exec_cmd(node, pfd);
		else
			add_to_commands(pid, commands);
	}	
	exec_node(node->right, pfd, commands);
	return (0);
}

*/