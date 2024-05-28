/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/28 10:11:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enable_raw_mode(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	disable_raw_mode(struct termios oterm)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &oterm) == -1)
	{
		perror("tcsetattr");
		exit(EXIT_FAILURE);
	}
}

void	ft_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	check_inline_param(int argc, char **argv, t_shell *sh)
{
	if (argc == 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		sh->input = ft_strdup(argv[2]);
		parse_input(sh);
		run_cmds(sh);
		free_new_prompt(sh);
		free(sh->input);
		free_args(sh->ms_envp);
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell			sh;
	struct termios	oterm;

	init_shell_struct(&sh);
	sh.ms_envp = copy_envp(envp, &sh);
	increase_shell_level(&sh);
	check_inline_param(argc, argv, &sh);
	if (tcgetattr(STDIN_FILENO, &oterm) == -1)
	{
		perror("tcgetattr failed");
		return (1);
	}
	sh.oterm = oterm;
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	while (1)
	{
		signal(SIGINT, ft_handler);
		enable_raw_mode();
		sh.input = readline("minishell > ");
		if (sh.input == NULL)
			exit_function();
		input_start(&sh, oterm);
	}
}
