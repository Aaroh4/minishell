/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/25 14:58:12 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

// Should here be more validation for cmd and hdocs?
static t_cmdn	*init_cmd_node(t_ntype type, t_shell *sh, t_bool last)
{
	t_cmdn	*new_cmdn;

	new_cmdn = malloc(sizeof(t_cmdn));
	if (new_cmdn != NULL)
	{
		new_cmdn->ntype = type;
		new_cmdn->left = NULL;
		new_cmdn->right = NULL;
		new_cmdn->cargs = NULL;
		new_cmdn->hdocs = NULL;
		if (type == COMMAND)
		{
			new_cmdn->cargs = sh->cmd;
			new_cmdn->hdocs = sh->hdocs;
		}
		new_cmdn->last = last;
		sh->cmd = NULL;
		sh->hdocs = NULL;
	}
	else
		errexit("error: ", "cmd node malloc", sh, 1);
	return (new_cmdn);
}

static void	trim_quote_alloc_hdoc(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->cmd[i] != NULL)
	{
		sh->cmd[i] = ft_strtrim(sh->cmd[i], " ");
		i++;
	}
	sh->cmd = ft_remove_quotes(sh->cmd);
	sh->hdocs = ft_calloc((i + 1), sizeof(int));
	if (sh->hdocs == NULL)
	{
		perror("hdocs malloc error");
		exit(1);
	}
	sh->hdocs[i] = -1;
}

char	*ft_give_fixed(char *str, int *i, char *temp)
{
	char	*temp2;
	int		j;

	j = 0;
	temp2 = malloc(sizeof(char) * ft_strlen(str) + ft_strlen(temp) + 3);
	while (temp[j] != '\0')
	{
		temp2[j] = temp[j];
		j++;
	}
	temp2[j] = '\"';
	j += 1;
	while (str[*i] != '\0')
	{
		if (str[*i] != '<' && str[*i - 1] == '<' && str[*i - 2] == '<')
			while (str[*i] == ' ')
				*i += 1;
		temp2[j] = str[*i];
		*i += 1;
		j += 1;
	}
	temp2[j] = '\"';
	j += 1;
	temp2[j] = '\0';
	return (temp2);
}

char	*ft_make_easy_heredoc(char *str)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i] != '\0')
	{
		if (str[i - 1] != '<' && str[i] == '<' && str[i + 1] == '<' && str[i
				+ 2] != '<')
		{
			temp = ft_give_fixed(str, &i, temp);
			return (temp);
		}
		else
		{
			temp[j] = str[i];
			i++;
			j++;
		}
	}
	temp[j] = '\0';
	return (temp);
}

static void	get_heredocs(t_shell *sh)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (sh->cmd[i] != NULL)
	{
		j = 0;
		while (sh->cmd[i][j] != '\0')
		{
			if (sh->cmd[i][j] == '<' && sh->cmd[i][j + 1] == '<' && sh->cmd[i][j
				+ 2] != '<')
			{
				sh->hdocs[i]++;
				temp = ft_heredoc(sh->cmd[i], sh->hdocs[i]);
			}
			j++;
		}
		if (sh->hdocs[i] > 0)
			sh->cmd[i] = temp;
		i++;
	}
}

static t_cmdn	*create_node(t_cmdn *current, t_shell *sh, int index)
{
	int	len;

	len = 0;
	while (sh->cmdarr[len] != NULL)
		len++;
	sh->cmdarr[index] = ft_make_easy_heredoc(sh->cmdarr[index]);
	sh->cmd = ft_split_time_space(sh->cmdarr[index], ' ');
	if (!(sh->cmd))
		errexit("error: ", "root malloc", sh, 1);
	trim_quote_alloc_hdoc(sh);
	get_heredocs(sh);
	if (index < len - 2)
	{
		current->left = init_cmd_node(COMMAND, sh, FALSE);
		current->right = init_cmd_node(PIPELINE, sh, FALSE);
		current = current->right;
	}
	else if (index == len - 2)
		current->left = init_cmd_node(COMMAND, sh, FALSE);
	else
		current->right = init_cmd_node(COMMAND, sh, TRUE);
	return (current);
}

void	parse_input(t_shell *sh)
{
	t_cmdn	*current;
	int		i;

	sh->root = init_cmd_node(PIPELINE, sh, FALSE);
	if (!(sh->root))
		errexit("error: ", "root malloc", sh, 1);
	sh->cmdarr = ft_split(sh->input, "|");
	current = sh->root;
	i = 0;
	while (sh->cmdarr[i] != NULL)
	{
		current = create_node(current, sh, i);
		i++;
	}
}
