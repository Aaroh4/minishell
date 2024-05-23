/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 14:23:00 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/23 13:33:29 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_cmd(t_cmdn *node, t_shell *sh, char *cwd)
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

char	**make_temp(t_shell *sh, char *str)
{
	int		i;
	char	**temp;

	i = 0;
	while (sh->ms_envp[i] != 0)
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (sh->ms_envp[i] != 0)
	{
		temp[i] = sh->ms_envp[i];
		i++;
	}
	free(sh->ms_envp);
	temp[i] = ft_subbstr(str, 0, ft_strlen(str) - 1);
	temp[i + 1] = NULL;
	return (temp);
}

char	*getting_multiple_param(t_shell *sh, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (sh->ms_envp[i] != 0)
	{
		j = 0;
		while (sh->ms_envp[i][j] == str[j] && sh->ms_envp[i][j] != '=')
			j++;
		if (str[j] == '=')
			break ;
		i++;
	}
	if (str[j] == '=')
	{
		free (sh->ms_envp[i]);
		sh->ms_envp[i] = ft_subbstr(str, 0, ft_strlen(str));
	}
	else
		sh->ms_envp = make_temp(sh, str);
	free(str);
	str = get_next_line(sh->efd[0]);
	return (str);
}

void	env_modify_loop(t_shell *sh, int a, char *cwd, char *str)
{
	char	*temp;

	str = get_next_line(sh->efd[0]);
	if (a == 2)
		str = ft_strjoin("OLDPWD=", cwd);
	if (str == NULL && a != 2)
		return ;
	while (str != NULL)
	{
		if (a == 1)
		{
			if (chdir(str) == -1)
			{
				printf("cd: %s: No such file or directory\n", str);
				free(str);
				return ;
			}
			temp = str;
			str = ft_strjoin("PWD=", temp);
			free(temp);
			modify_env(sh, 2, cwd);
		}
		str = getting_multiple_param(sh, str);
	}
}

void	modify_env(t_shell *sh, int a, char *cwd)
{
	char	*str;

	close(sh->efd[1]);
	str = NULL;
	if (sh->cmdcount == 1)
		env_modify_loop(sh, a, cwd, str);
	close(sh->efd[0]);
}

void	check_builtin(t_cmdn *node, t_shell *sh, char *cwd)
{
	if (!ft_strncmp("export", node->cargs[0], ft_strlen(node->cargs[0])))
		modify_env(sh, 0, cwd);
	else if (!ft_strncmp("unset", node->cargs[0], ft_strlen(node->cargs[0])))
		sh->ms_envp = remove_array(sh, sh->ms_envp);
	else if (!ft_strncmp("cd", node->cargs[0], ft_strlen(node->cargs[0])))
		modify_env(sh, 1, cwd);
	else if (!ft_strncmp("exit", node->cargs[0], ft_strlen(node->cargs[0])))
		exit_in_main(node, sh);
	if (sh->cmdcount > 1)
		switch_pipe_fds(sh);
}

void	make_child(t_cmdn *node, t_shell *sh, t_intvec *commands, char *cwd)
{
	int		pid;

	pid = 0;
	populate_env_vars(node, sh);
	pid = fork();
	if (pid == -1)
	{
		sh->status = wait_for(commands);
		free_intvec(commands);
		errexit("Error:", "fork failure", NULL, sh);
	}
	else if (pid == 0)
	{
		if (pipe(sh->hfd) == -1)
			errexit("error :", "pipe initialization", NULL, sh);
		free_intvec(commands);
		exec_cmd(node, sh, cwd);
	}
	else
	{
		check_builtin(node, sh, cwd);
		if (commands != NULL)
			add_to_intvec(commands, pid, sh);
	}
}

static int	exec_node(t_cmdn *node, t_shell *sh, t_intvec *commands)
{
	char	buffer[1024];
	char	*cwd;

	cwd = getcwd(buffer, sizeof(buffer));
	if (cwd == NULL)
		errexit("error:", "getcwd", NULL, sh);
	if (node == NULL)
		return (0);
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
