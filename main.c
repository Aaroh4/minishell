/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/23 15:28:48 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void	enable_raw_mode(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		perror("tcgetattr");
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
		perror("tcsetattr");
}

void	disable_raw_mode(struct termios oterm)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &oterm) == -1)
		perror("tcsetattr");
}

void	ft_handler(int signum)
{
	signum = 1;
	rl_replace_line("", 0);
	write(1, "\n", signum);
	rl_on_new_line();
	rl_redisplay();
}

// BS function to prevent compiler warnings
// Maybe later actual parameters for minishell will be used
// Right now it's just to get envp
static int	handle_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	while (argv[i] && i < argc)
		i++;
	return (i);
}

// Removed free_args(sh->ms_envp); from end
int	main(int argc, char **argv, char **envp)
{
	t_shell			sh;
	struct termios	oterm;

	init_shell_struct(&sh);
	if (tcgetattr(STDIN_FILENO, &oterm) == -1)
		perror("tcgetattr");
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	handle_arguments(argc, argv);
	sh.ms_envp = copy_envp(envp);
	while (1)
	{
		if (pipe(sh.pfd) == -1)
			errexit("Error :", "pipe initialization", &sh, 1);
		enable_raw_mode();
		sh.input = readline("minishell > ");
		if (sh.input == NULL || !ft_strncmp(sh.input, "exit", 5))
			exit_builtin(&sh);
		add_history(sh.input);
		parse_input(&sh);
		run_cmds(&sh);
		free_new_prompt(&sh);
		disable_raw_mode(oterm);
	}
}

/*
// ENVP test main:
int	main(int argc, char **argv, char **envp)
{
	char	**ms_envp;
	char	*input;
	char	*str;

	if (argc == 2)
	{
		handle_arguments(argc, argv);
		ms_envp = copy_envp(envp);
		input = "Used: $USER, shell: $SHELL, not working $NOT_WORK end.";
		str = ft_strdup(input);
		ft_putendl_fd(str, 2);
		str = replace_envp(str, ms_envp);
		ft_putendl_fd(str, 2);
		free(str);
	}
	return (0);
}
*/