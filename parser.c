/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/12 15:45:34 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_cmdn	*init_cmd_node(t_ntype type, char **cmd, t_bool last)
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
	}
	return (new_cmdn);
}

static t_cmdn	*create_node(t_cmdn *current, char **cmdarr, int i, int len)
{
	char	**cmd;
	int		j;

	//cmd = ft_split_time_space(cmdarr[i], ' ');
	cmd = ft_split(cmdarr[i], " ");
	if (!cmd)
		exit(1);
	j = 0;
	while (cmd[j] != '\0')
	{
		cmd[j] = trim_string(cmd[j]);
		j++;
	}
	if (i < len - 2)
	{
		current->left = init_cmd_node(COMMAND, cmd, FALSE);
		current->right = init_cmd_node(PIPELINE, NULL, FALSE);
		current = current->right;
	}
	else if (i == len - 2)
		current->left = init_cmd_node(COMMAND, cmd, FALSE);
	else
		current->right = init_cmd_node(COMMAND, cmd, TRUE);
	return (current);
}

void	parse_input(char *input, t_cmdn **root)
{
	char	**cmdarr;
	t_cmdn	*current;
	int		i;
	int 	len;

	i = 0;
	*root = init_cmd_node(PIPELINE, NULL, FALSE);
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

/*
char	*check_cmd(char *string)
{
	int		i;
	char 	*cmd_strings = {"echo", "cd", "pwd"};

	i = 0;
	while (cmd_strings[i] != '\0')
	{
		if (!ft_strncmp(string, cmd_strings[i], ft_strlen(&cmd_strings[i])))
		{
			return (cmd_strings[i]);
		}
		i++;
	}
	return (NULL);
}
*/

/*
void	print_cmdn(t_cmdn *croot, int tabs)
{
	int	i;

	if (croot == NULL)
	{
		printf("<empty>\n");
		return;
	}
	i = 0;
	while (i++ < tabs)
		printf("\t");
	i = 0;
	printf("type	: %d\n", croot->ntype);
	while (i++ < tabs)
		printf("\t");
	i = 0;
	printf("symbol	: %d\n", croot->symbol);
	while (croot->children[i] != 0)
	{
		print_cmdn(croot->children[i], ++tabs);
		i++;
	}
}
*/