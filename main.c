/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/10 12:59:52 by mburakow         ###   ########.fr       */
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
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}

void	disableRawMode(struct termios oterm)
{
	 if (tcsetattr(STDIN_FILENO, TCSANOW, &oterm) == -1)
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

int	main(int argc, char **argv, char **envp)
{
	t_cmdn	*cmd_root;
	char	*input;
	char	**arr;
	struct termios oterm;

	if (tcgetattr(STDIN_FILENO, &oterm) == -1)
		perror("tcgetattr");
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);

	rl_clear_history();
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd error");
	while (1)
	{
		enableRawMode();
		input = readline("minishell > ");
		if (input == NULL || !ft_strncmp(input, "exit", 5))
			exit_builtin();
		disableRawMode(oterm);
		add_history(input);
		if (!ft_strncmp(input, "pwd", 5))
			pwd_builtin();
		arr = ft_split(input, " ");
		if (arr[0] != '\0' && !ft_strncmp(arr[0], "cd", 2))
			cd_builtin(cwd, arr);
		if (arr[0] != '\0' && !ft_strncmp(arr[0], "echo", 2))
			echo_builtin(arr);
		free(input);
		while(*arr != NULL)
			free(*arr++);
	}
}
