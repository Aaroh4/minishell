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

void	ft_signal_handle(int signal_num)
{
	int	i;

	i = 0;
	if (i == signal_num)
		i = 1;
}

void	enable_raw_mode(void)
{
	struct termios	orig_termios;
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &orig_termios);
	raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmdn	*cmd_root;
	char	*input;

	enable_raw_mode();
	if (argc > 1)
		argc++;
	if (argv[0])
		argv[0] = "Minishelli";
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_handle);
	cmd_root = init_cmd_node(PIPELINE, NULL, envp);
	while (1)
	{
		input = readline("minishell > ");
		if (!ft_strncmp(input, "break", 5) || input == NULL)
			return (0);
		parse_input(input, &cmd_root, envp);
		print_cmdn(cmd_root);
		run_cmds(cmd_root);
	}
}
