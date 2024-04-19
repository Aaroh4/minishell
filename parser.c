/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/19 18:14:45 by mburakow         ###   ########.fr       */
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

char	**ft_remove_quotes(char **cmd)
{
	int		i;
	int		j;

	i = 1;
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '\"')
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
	return (cmd);
}

static t_cmdn	*create_node(t_cmdn *current, char **cmdarr, int i, int len)
{
	char	**cmd;
	int		*hdocs;
	int		j;
	char	*temp;

	cmd = ft_split_time_space(cmdarr[i], ' ');
	if (!cmd)
		exit(1);
	j = 0;
	while (cmd[j] != NULL)
	{
		cmd[j] = ft_strtrim(cmd[j], " ");
		j++;
	}
	cmd = ft_remove_quotes(cmd);
	hdocs = ft_calloc((j + 1), sizeof(int));
	if (hdocs == NULL)
	{
		perror("hdocs malloc error");
		exit (1);
	}
	hdocs[j] = -1;
	j = 0;
	while (cmd[j] != NULL)
	{
		if (cmd[j][0] == '<' && cmd[j][1]
			== '<' && cmd[j][2] != '<')
		{
			hdocs[j]++;
			temp = ft_heredoc(cmd[j], hdocs[j]);
		}
		j++;
	}
	if (hdocs[j] > 0)
	{
		cmd[j] = temp;
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
	// free(temp);
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
	while (cmdarr[len] != NULL)
		len++;
	//ft_putstr_fd("Number of commands: ", 2);
	//ft_putnbr_fd(len, 2);
	//ft_putchar_fd('\n', 2);
	while (cmdarr[i] != NULL)
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
