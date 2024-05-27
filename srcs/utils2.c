/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:32:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/27 17:52:51 by mburakow         ###   ########.fr       */
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

void	unset_loop(int *j, char *str, char **temp, char **temp_ms)
{
	int	k;

	k = 0;
	while (temp_ms[*j] != 0)
	{
		if (ft_strncmp(str, temp_ms[*j], ft_strlen(str)))
		{
			temp[k] = temp_ms[*j];
			k++;
		}
		else
			free(temp_ms[*j]);
		*j += 1;
	}
}

char	**unset_remove_from_array(t_shell *sh, char **temp_ms)
{
	int		j;
	char	*str;
	char	*tempstr;
	char	**temp;

	close (sh->efd[1]);
	if (sh->cmdcount == 1)
	{
		tempstr = get_next_line(sh->efd[0]);
		if (tempstr == NULL)
			return (temp_ms);
		str = ft_substr(tempstr, 0, ft_strlen(tempstr) - 1);
		free(tempstr);
		j = count_array(temp_ms);
		temp = malloc(sizeof(char *) * (j + 1));
		j = 0;
		unset_loop(&j, str, temp, temp_ms);
		temp[j] = NULL;
		temp = unset_remove_from_array(sh, temp);
		free(temp_ms);
		free(str);
		return (temp);
	}
	else
		return (temp_ms);
}
