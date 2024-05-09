/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/09 16:19:21 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// Implementing the bash -c flag to run one command without
// entering the prompt loop. For use with tester for example.
static int	check_inline_param(int argc, char **argv, t_shell *sh, struct termios	oterm)
{
	int	i;

	i = 1;
	while (argv[i] && i < argc)
	{
		if (!ft_strncmp(argv[i], "-c", ft_strlen(argv[i])))
		{
			if (pipe(sh->pfd) == -1)
				errexit("Error :", "pipe initialization", NULL, sh);
			enable_raw_mode();
			sh->input = ft_strdup(argv[i + 1]);
			parse_input(sh);
			run_cmds(sh);
			disable_raw_mode(oterm);
			free_new_prompt(sh);
			free(sh->input);
			free_args(sh->ms_envp);
			exit(0);
		}
		i++;
	}
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
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	sh.ms_envp = copy_envp(envp, &sh);
	check_inline_param(argc, argv, &sh, oterm);
	while (1)
	{
		signal(SIGINT, ft_handler);
		if (pipe(sh.pfd) == -1 || pipe(sh.efd) == -1)
			errexit("error :", "pipe initialization", NULL, &sh);
		enable_raw_mode();
		sh.input = readline("minishell > ");
		if (sh.input == NULL)
			exit (0);
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