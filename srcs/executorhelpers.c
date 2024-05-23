/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorhelpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:20:13 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/23 11:01:37 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_input_pipes(t_shell *sh)
{
	close (sh->hfd[0]);
	//if (sh->cmdcount > 1)
		close(sh->pfd[0][0]);
		close(sh->pfd[1][0]);
}

void	close_output_pipes(t_shell *sh)
{
	close (sh->hfd[1]);
	//if (sh->cmdcount > 1)
		close(sh->pfd[0][1]);
		close(sh->pfd[1][1]);
}

void	switch_pipe_fds(t_shell *sh)
{
	close(sh->pfd[0][0]);
	close(sh->pfd[0][1]);
	sh->pfd[0][0] = sh->pfd[1][0];
	sh->pfd[0][1] = sh->pfd[1][1];
	if (pipe(sh->pfd[1]) == -1)
		errexit("error :", "pipe initialization", NULL, sh);
}

char	*get_msenv(char *name, t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->ms_envp[i] != NULL)
	{
		if (!ft_strncmp(sh->ms_envp[i], name, ft_strlen(name)))
			return (&sh->ms_envp[i][5]);
		i++;
	}
	return (NULL);
}
