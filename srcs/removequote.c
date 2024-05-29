/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:50:59 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/29 11:54:50 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quotepair(char *strret[2], int i, int j, t_shell *sh)
{
	char	*temp;
	char	*temp2;

	temp = ft_substr(strret[0], i + 1, j - (i + 1));
	if (!strret[1])
		strret[1] = ft_strdup("");
	if (strret[0][i] == '\"')
		temp = replace_envp_tags(temp, sh);
	temp2 = ft_strjoin(strret[1], temp);
	free(temp);
	free(strret[1]);
	strret[1] = temp2;
}

static void	loop_remove_quotes(char *s[2], int i[3], t_shell *sh)
{
	while (s[0][i[1]] != '\0')
	{
		if (s[0][i[1]] == s[0][i[0]])
		{
			remove_quotepair(s, i[0], i[1], sh);
			i[0] = i[1];
			i[2] = i[1];
			break ;
		}
		i[1]++;
	}
}

static void	remove_and_replace(char *s[2], char *tmp[2], int i[3], t_shell *sh)
{
	int	k;

	if (s[0][i[0]] == '\"' || s[0][i[0]] == '\'')
	{
		k = 0;
		if (i[1] > 0)
			k = 1;
		tmp[0] = replace_envp_tags(ft_substr(s[0], i[1] + k, i[0]
					- (i[1] + k)), sh);
		if (!s[1])
			s[1] = ft_strdup("");
		tmp[1] = ft_strjoin(s[1], tmp[0]);
		free(s[1]);
		free(tmp[0]);
		s[1] = tmp[1];
		i[1] = i[0] + 1;
		loop_remove_quotes(s, i, sh);
	}
}

static void	finish_and_free(char *s[2], char *tmp[2], int i[3], t_shell *sh)
{
	tmp[0] = ft_substr(s[0], i[2], (ft_strlen(s[0]) - i[2] - 1));
	tmp[0] = replace_envp_tags(tmp[0], sh);
	tmp[1] = ft_strjoin(s[1], tmp[0]);
	free(tmp[0]);
	free(s[1]);
	s[1] = tmp[1];
}

char	*remove_quote_level(char *str, t_shell *sh)
{
	int		i[3];
	char	*s[2];
	char	*tmp[2];

	if (test_quote_level(str) == -1)
		return (replace_envp_tags(str, sh));
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	s[0] = str;
	s[1] = NULL;
	tmp[0] = NULL;
	tmp[1] = NULL;
	while (s[0][i[0]] != '\0')
	{
		remove_and_replace(s, tmp, i, sh);
		i[0]++;
	}
	finish_and_free(s, tmp, i, sh);
	free(str);
	return (s[1]);
}
