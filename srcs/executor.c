/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:23:00 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/24 15:47:59 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_cmdn *node, t_shell *sh, char *cwd)
{
	char	**path_array;
	char	*cmdp;

	sh->status = open_redirects(node, sh);
	if (check_hdocs(node))
		if (dup2(sh->hfd[0], STDIN_FILENO) == -1)
			errexit("error :", "dup2 failed", NULL, sh);
	close_input_pipes(sh);
	handle_heredocs(node, sh);
	close_output_pipes(sh);
	path_array = NULL;
	cmdp = NULL;
	if (!(exec_builtin(node, sh, cwd)))
	{
		close (sh->efd[0]);
		close (sh->efd[1]);
		path_array = ft_split(get_msenv("PATH", sh), ":");
		cmdp = get_exec_path(path_array, node->cargs[0], sh);
		free_args(path_array);
		if (!node->cargs[0] || !*node->cargs || !cmdp || execve(cmdp,
				node->cargs, sh->ms_envp) == -1)
			errexitcode(node->cargs[0], ": command not found", 127, sh);
	}
	exit(EXIT_SUCCESS);
}

static void	clean_cargs_hdrd(t_cmdn *node)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = 0;
	while (node->cargs[size] != NULL)
		size++;
	while (i < size)
	{
		if (node->hdocs[i] > 0 || node->redirs[i] > 0)
		{
			free(node->cargs[i]);
			j = i;
			while (j < size - 1)
			{
				node->cargs[j] = node->cargs[j + 1];
				j++;
			}
			size--;
			node->cargs[size] = NULL;
			i--;
		}
		i++;
	}
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

static int	exec_node(t_cmdn *node, t_shell *sh, t_intvec *commands)
{
	char	buffer[1024];
	char	*cwd;

	if (node == NULL)
		return (0);
	cwd = NULL;
	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd == NULL)
		errexit("error:", "getcwd", NULL, sh);
	if (node->left != NULL)
		exec_node(node->left, sh, commands);
	if (node->ntype == COMMAND)
		make_child(node, sh, commands, cwd);
	if (node->right != NULL)
		exec_node(node->right, sh, commands);
	return (0);
}

int	run_cmds(t_shell *sh)
{
	t_intvec	*commands;

	if (sh->root == NULL)
		return (1);
	commands = create_intvec(sh);
	create_pipes(sh);
	exec_node(sh->root, sh, commands);
	close_ext_pipes(sh);
	sh->status = wait_for(commands);
	free_intvec(commands);
	return (0);
}
