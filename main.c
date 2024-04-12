/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/12 15:18:05 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <fcntl.h>

void enableRawMode() {
	struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1)
		perror("tcgetattr");
    term.c_lflag &= ~(ECHOCTL);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1)
		perror("tcsetattr");
}

void	disableRawMode(struct termios oterm)
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

int	main(void)
{
	t_cmdn			*cmd_root;
	char			*input;
	struct termios 	oterm;
	int				pfd[2];

	if (tcgetattr(STDIN_FILENO, &oterm) == -1)
		perror("tcgetattr");
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	if (pipe(pfd) == -1)
		perror("pipe init error.");
	while (1)
	{
		if (pipe(pfd) == -1)
			perror("pipe init error.");
		enableRawMode();
		input = readline("minishell > ");
		if (input == NULL || !ft_strncmp(input, "exit", 5))
			exit_builtin();
		add_history(input);
		parse_input(input, &cmd_root);
	//	ft_putendl_fd("###########", 2);
	//	print_cmdn(cmd_root);
	//	ft_putendl_fd("###########", 2);
		run_cmds(cmd_root, pfd);
		free(input);
		free_cmdn(cmd_root);
		disableRawMode(oterm);
		close(pfd[0]);
		close(pfd[1]);
	}
}
