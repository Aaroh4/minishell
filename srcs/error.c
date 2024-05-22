/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:27:19 by mburakow          #+#    #+#             */
/*   Updated: 2024/05/22 10:10:31 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errexit(char *msg1, char *msg2, char *msg3, t_shell *sh)
{
	disable_raw_mode(sh->oterm);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putstr_fd(msg2, 2);
	if (msg3)
		ft_putendl_fd(msg3, 2);
	else
		ft_putendl_fd("", 2);
	free_cmdn(sh->root);
	free_args(sh->cmdarr);
	if (sh->cmdcount > 1)
		close_ext_pipes(sh);
	free_args(sh->cmd);
	free(sh->hdocs);
	sh->status = 1;
	exit(sh->status);
}

void	errexitcode(char *msg1, char *msg2, int status, t_shell *sh)
{
	disable_raw_mode(sh->oterm);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg1, 2);
	ft_putendl_fd(msg2, 2);
	free_cmdn(sh->root);
	free_args(sh->cmdarr);
	if (sh->cmdcount > 1)
		close_ext_pipes(sh);
	free_args(sh->cmd);
	free(sh->hdocs);
	sh->status = status;
	exit(sh->status);
}