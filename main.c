/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/03 15:10:05 by mburakow         ###   ########.fr       */
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


void ft_signal_handle(int signal_num) {
   // printf("Received signal: %d\n", signal_num);
	int	i;

	i = 0;
	if (i == signal_num)
		i = 1;
}

void enableRawMode() {
	struct termios orig_termios;
	tcgetattr(STDIN_FILENO, &orig_termios);

	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	main(void)
{
	t_cmdn	*cmd_root;
	char	*input;

	enableRawMode();

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_handle);

	cmd_root = init_cmdn(PIPELINE, NULL);
	while (1)
	{
		input = readline("minishell > ");
		if (!ft_strncmp(input, "break", 5) || input == NULL)
			return (0);
		parse_input(input, &cmd_root);
		print_cmdn(cmd_root);
	}
}
