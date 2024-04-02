/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 11:20:14 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/02 14:42:56 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_cmdn *init_cmdn(t_ntype type, char *symbol)
{
	t_cmdn	*new_cmdn;
	int		i;

	new_cmdn = malloc(sizeof(t_cmdn));
	if (new_cmdn != NULL)
	{
		new_cmdn->ntype = type;
		new_cmdn->symbol = symbol;
		i = 0;
		while (i < NUM_CHILDREN)
		{
			new_cmdn->children[i] = NULL;
			i++;
		}
	}
	return (new_cmdn);
}

char	*check_cmd(char *string)
{
	int		i;
	char 	*cmd_strings = {"echo", "cd", "pwd"};

	i = 0;
	while (cmd_strings[i] != '\0')
	{
		if (!ft_strncmp(string, cmd_strings[i], ft_strlen(cmd_strings[i])))
		{
			return (cmd_strings[i]);
		}
		i++;
	}
	return (NULL);
}

void	parse_input(char *input, t_cmdn *croot)
{
	char	**arr;
	t_cmdn	*current;
	int		i;

	i = 0;
	arr = ft_split(input, " ");
	current = croot;
	while (arr[i] != '\0')
	{	
		check_cmd(arr[i]);
		croot->symbol = arr[i];
		printf("%s\n", arr[i]);
		i++;
	}

	while (arr[i] != '\0')
	{
		check_cmd(arr[i]);
		croot->symbol = arr[i];
		printf("%s\n", arr[i]);
		i++;
	}
}

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