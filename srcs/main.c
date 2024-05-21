/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:43 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/21 16:19:33 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (signum)
		signum--;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

// Implementing the bash -c flag to run one command without
// entering the prompt loop. For use with tester for example.
static int	check_inline_param(int argc, char **argv, t_shell *sh, struct termios oterm)
{
	int	i;

	i = 1;
	while (argv[i] && i < argc)
	{
		if (!ft_strncmp(argv[i], "-c", ft_strlen(argv[i])))
		{
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

int	main(int argc, char **argv, char **envp)
{
	t_shell			sh;
	struct termios	oterm;
	int				shlvl;

	init_shell_struct(&sh);
	if (tcgetattr(STDIN_FILENO, &oterm) == -1)
	{
		dprintf(2, "tcsetattr() failed:\n");
		return (1);
		// perror("tcgetattr");
	}
	sh.oterm = oterm;
	signal(SIGQUIT, SIG_IGN);
	rl_clear_history();
	sh.ms_envp = copy_envp(envp, &sh);
	shlvl = ft_atoi(get_env_val_by_name("SHLVL", &sh)) + 1;
	modify_env_internal("SHLVL", ft_itoa(shlvl), &sh);
	check_inline_param(argc, argv, &sh, oterm);
	while (1)
	{
		signal(SIGINT, ft_handler);
		enable_raw_mode();
		sh.input = readline("minishell > ");
		if (sh.input == NULL)
		{
			write(1, "exit\n", 5);
			exit (0);
		}
		add_history(sh.input);
		parse_input(&sh);
		run_cmds(&sh);
		free_new_prompt(&sh);
		disable_raw_mode(oterm);
	}
}
