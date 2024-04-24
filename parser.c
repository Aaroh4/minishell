/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/24 12:23:32 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_cmdn	*init_cmd_node(t_ntype type, char **cmd, t_bool last, int *hdocs)
{
	t_cmdn	*new_cmdn;

	new_cmdn = malloc(sizeof(t_cmdn));
	if (new_cmdn != NULL)
	{
		new_cmdn->ntype = type;
		new_cmdn->left = NULL;
		new_cmdn->right = NULL;
		new_cmdn->cargs = NULL;
		if (cmd != NULL)
			new_cmdn->cargs = cmd;
		new_cmdn->last = last;
		new_cmdn->hdocs = hdocs;
	}
	return (new_cmdn);
}

char	**ft_remove_slash(char **cmd)
{
	int		i;
	int		j;

	i = 1;
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j + 1] == '\"' && cmd[i][j] == '\\')
			{
				while (cmd[i][j] != '\0')
				{
					cmd[i][j] = cmd[i][j + 1];
					j++;
					//printf("%s:%d:%d\n", cmd[i], i, j);
				}
				j = 0;
			}
			j++;
		}
		i++;
	}
	return (cmd);
}

char	**ft_remove_quotes(char **cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '\"' && cmd[i][j - 1] != '\\')
			{
				while (cmd[i][j] != '\0')
				{
					cmd[i][j] = cmd[i][j + 1];
					j++;
				}
				j = 0;
			}
			j++;
		}
		i++;
	}
	cmd = ft_remove_slash(cmd);
	return (cmd);
}

char	*ft_give_fixed(char *str, int *i, char *temp)
{
	char	*temp2;
	int		k;
	int		j;

	k = 0;
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
		if (str[i - 1] != '<'
			&& str[i] == '<' && str[i + 1] == '<' && str[i + 2] != '<')
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

static t_cmdn	*create_node(t_cmdn *current, char **cmdarr, int i, int len)
{
	char	**cmd;
	int		*hdocs;
					//int		*hdoc_index;
	int		j;
	int		k;
	char	*temp;

	k = 0;

	len = 0;
	cmdarr[i] = ft_make_easy_heredoc(cmdarr[i]);
	cmd = ft_split_time_space(cmdarr[i], ' ');
	cmd = ft_remove_quotes(cmd);
	if (!cmd)
		exit(1);
	// trim_string(cmd[0]);
	//hdocs = ft_calloc(len, sizeof(int));
	j = 0;
	while (cmd[j] != NULL)
	{
		cmd[j] = ft_strtrim(cmd[j], " ");
		j++;
	}
	hdocs = ft_calloc((j + 1), sizeof(int));
	if (hdocs == NULL)
	{
		perror("hdocs malloc error");
		exit (1);
	}
	hdocs[j] = -1;
	j--;
	while (j >= 0)
	{
		while (cmd[j][k] != '\0')
		{
			if (cmd[j][k] == '<' && cmd[j][k + 1]
				== '<' && cmd[j][k + 2] != '<')
			{
				hdocs[j]++;
				temp = ft_heredoc(cmd[j], hdocs[j]);
			}
			k++;
		}
		if (hdocs[j] > 0)
			cmd[j] = temp;
		j--;
	}
	if (i < len - 2)
	{
		current->left = init_cmd_node(COMMAND, cmd, FALSE, hdocs);
		current->right = init_cmd_node(PIPELINE, NULL, FALSE, hdocs);
		current = current->right;
	}
	else if (i == len - 2)
		current->left = init_cmd_node(COMMAND, cmd, FALSE, hdocs);
	else
		current->right = init_cmd_node(COMMAND, cmd, TRUE, hdocs);
//	free(temp); 
	return (current); 
}

void	parse_input(char *input, t_cmdn **root)
{
	char	**cmdarr;
	t_cmdn	*current;
	int		i;
	int		len;

	i = 0;
	*root = init_cmd_node(PIPELINE, NULL, FALSE, NULL);
	if (!(*root))
		exit(1);
	cmdarr = ft_split(input, "|");
	current = *root;
	len = 0;
	while (cmdarr[len] != 0)
		len++;
	//ft_putstr_fd("Number of commands: ", 2);
	//ft_putnbr_fd(len, 2);
	//ft_putchar_fd('\n', 2);
	while (cmdarr[i] != 0)
	{
		current = create_node(current, cmdarr, i, len);
		i++;
	}
}

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
