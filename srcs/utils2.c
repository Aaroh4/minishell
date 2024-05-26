/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:50:59 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/26 17:30:27 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmdn(t_cmdn *node)
{
	int	i;

	if (node == NULL)
		return ;
	print_cmdn(node->left);
	i = 0;
	if (node->ntype == COMMAND)
		ft_putendl_fd("COMMAND:", 2);
	if (node->ntype == PIPELINE)
		ft_putendl_fd("PIPELINE:", 2);
	while (node->cargs && node->cargs[i] != 0)
	{
		if (i != 0)
			ft_putchar_fd('\t', 2);
		ft_putendl_fd(node->cargs[i], 2);
		i++;
	}
	ft_putnbr_fd(node->last, 2);
	ft_putchar_fd('\n', 2);
	print_cmdn(node->right);
}

void	remove_quotepair(char *strret[2], int i, int j, t_shell *sh)
{
	char *temp;
	char *temp2;

	temp = ft_substr(strret[0], i + 1, j - (i + 1));
	// dprintf(2, "Substr: %s quote: %c\n", temp, strret[0][i]);
	if (!strret[1])
		strret[1] = ft_strdup("");
	if (strret[0][i] == '\"')
		temp = replace_envp_tags(temp, sh);
	temp2 = ft_strjoin(strret[1], temp);
	free(temp);
	free(strret[1]);
	strret[1] = temp2;
	// dprintf(2, "Ret: %s\n", strret[1]);
}

// Strret[0] is the source, strret[1] the final array
// Need to handle areas between quotes, in the beginning and end that are not inside quotes
char	*remove_quote_level(char *str, t_shell *sh)
{
	int		i;
	int		j;
	int		lj;
	int		k;
	char	*s[2];
	char	*tmp[2];

	if (test_quote_level(str) == -1)
		return (str);
	i = 0;
	j = 0;
	lj = 0;
	k = 0;
	s[0] = str;
	s[1] = NULL;
	tmp[0] = NULL;
	tmp[1] = NULL;
	dprintf(2, "String handled: %s\n", str);
	while (s[0][i] != '\0')
	{
		if (s[0][i] == '\"' || s[0][i] == '\'')
		{
			if (j > 0)
				k = 1;
			tmp[0] = replace_envp_tags(ft_substr(s[0], j + k, i - (j + k)), sh);
			dprintf(2, "Tmp is: %s\n", tmp[0]);
			tmp[1] = ft_strjoin(s[1], tmp[0]);
			free(s[1]);
			free(tmp[0]);
			s[1] = tmp[1];
			j = i + 1;
			while (j != '\0')
			{
				if (s[0][j] == s[0][i])
				{
					remove_quotepair(s, i, j, sh);
					dprintf(2, "s[1] is: %s\n", s[1]);
					i = j;
					lj = j;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	dprintf(2, "Ret wo tail: %s\n", s[1]);
	dprintf(2, "lj is: %d len: %d\n", lj, ft_strlen(s[0]));
	dprintf(2, "char at lj: %d c: %c\n", lj, s[0][lj]);
	dprintf(2, "Whole string: %s\n", s[0]);
	tmp[0] = ft_substr(s[0], lj + 1, ft_strlen(s[0]) - lj);
	dprintf(2, "Tmp almost final is: %s\n", tmp[0]);
	tmp[1] = replace_envp_tags(tmp[0], sh);
	//free(tmp[0]);
	dprintf(2, "Tmp final is: %s\n", tmp[1]);
	tmp[0] = ft_strjoin(s[1], tmp[0]);
	//free(s[1]);
	//free(tmp[1]);
	s[1] = tmp[0];
	dprintf(2, "Ret with tail: %s\n", s[1]);
	return (s[1]);
}

char	**remove_quotes_ex_export(char **cmd, t_shell *sh)
{
	t_bool	export_flag;
	int		i;

	export_flag = FALSE;
	i = -1;
	while (cmd[++i] != NULL)
	{
		if (!ft_strncmp(cmd[i], "export", ft_strlen(cmd[i])))
			export_flag = TRUE;
		if (export_flag && (cmd[i][0] == '<' || cmd[i][0] == '>'))
			export_flag = FALSE;
		if (!export_flag)
			remove_quote_level(cmd[i], sh);
	}
	return (cmd);
}

// At the moment accounts only for space characters,
//	are other characters necessary?

char	*trim_string(char *str)
{
	int		i;
	char	*end;
	char	*curs;

	i = 0;
	if (!str || str[0] == '\0' || str[0] == 0)
		return (str);
	while ((unsigned char)str[i] == 32)
		i++;
	curs = &str[i];
	i = 0;
	if (*curs == '\0')
	{
		str[i] = *curs;
		return (str);
	}
	while (*curs != '\0')
	{
		str[i++] = *curs;
		curs++;
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && (unsigned char)*end == 32)
		end--;
	end[1] = '\0';
	return (str);
}

void	print_char_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		dprintf(2, "[%d] ", i);
		dprintf(2, "%s\n", arr[i++]);
	}
}

char	test_quote_level(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			j = ft_strlen(str) - 1;
			while (j > i)
			{
				if (str[j] == str[i])
					return (str[i]);
				j--;
			}
		}
		i++;
	}
	return (-1);	
}
