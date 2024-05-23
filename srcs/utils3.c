/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:32:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/23 14:32:12 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_start(t_shell *sh, struct termios oterm)
{
	add_history(sh->input);
	parse_input(sh);
	run_cmds(sh);
	free_new_prompt(sh);
	disable_raw_mode(oterm);
}

void	exit_function(void)
{
	write(1, "exit\n", 5);
	exit (0);
}
