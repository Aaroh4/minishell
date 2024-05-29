/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/28 16:15:17 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	enable_raw_mode(int is_on)
{
	struct termios	new_attr;

	tcgetattr(STDIN_FILENO, &new_attr);
	if (!is_on)
		new_attr.c_lflag &= ~ECHOCTL;
	else
		new_attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}

void	ft_handler(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
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
	rl_clear_history();
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handler);
		enable_raw_mode(0);
		sh.input = readline("minishell > ");
		enable_raw_mode(1);
		if (sh.input == NULL)
			exit_function();
		input_start(&sh);
	}
}
