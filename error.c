/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:27:19 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/22 18:22:15 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// What should we free here?	
void	errexit(char *msg1, char *msg2, t_shell *sh, int exitcode)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putendl_fd(msg2, 2);
	free_args(sh->cmdarr);
	close(sh->pfd[0]);
	close(sh->pfd[1]);
	exit(exitcode);
}