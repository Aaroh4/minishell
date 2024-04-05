/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/05 15:01:26 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_cmdn	*init_cmdn(t_ntype type, char **cmd)
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
	}
	return (new_cmdn);
}

static t_cmdn	*create_node(t_cmdn *current, char **cmdarr, int i)
{
	char	**cmd;

	cmd = ft_split(cmdarr[i], " ");
	if (!cmd)
		exit(1);
	if (i == ft_strlen(*cmdarr) - 1)
	{
		current->left = init_cmdn(COMMAND, cmd);
		current->right = init_cmdn(PIPELINE, NULL);
		current = current->right;
	}
	else
		current->right = init_cmdn(COMMAND, cmd);
	return (current);
}

void	parse_input(char *input, t_cmdn **root)
{
	char	**cmdarr;
	t_cmdn	*current;
	int		i;

	i = 0;
	*root = init_cmdn(PIPELINE, NULL);
	if (!(*root))
		exit(1);
	cmdarr = ft_split(input, "|");
	current = *root;
	while (cmdarr[i] != NULL)
	{
		// printf("%s\n", cmdarr[i]);
		current = create_node(current, cmdarr, i);
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
	while (node->cargs && node->cargs[i] != 0)
	{
		if (i != 0)
			printf("\t");
		printf("%s\n", node->cargs[i]);
		i++;
	}
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