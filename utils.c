/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:07:48 by mburakow          #+#    #+#             */
/*   Updated: 2024/04/04 19:58:54 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

/*
t_dynint*	create_dynamic_int_array() 
{
    t_dynint *dynarr = (t_dynint*)malloc(sizeof(t_dynint));
    if (dynarr == NULL) {
		exit(1);
    dynarr->array = (int*)malloc(INITIAL_SIZE * sizeof(int));
    if (dynarr->array == NULL) 
	{
        free(dynarr);
        exit(1);
    }
    dynarr->size = 0;
    dynarr->capacity = INITIAL_SIZE;
    return dynarr;
}

void	expand_dynamic_int_array(t_dynint *dynarr) 
{
    size_t new_capacity = dynarr->capacity * 2;
    int *newarr = (int*)realloc(dynarr->array, new_capacity * sizeof(int));
    if (newarr == NULL) 
	{
        free(dynarr->array);
        free(dynarr);
        exit(1);
    }
    dynarr->array = newarr;
    dynarr->capacity = new_capacity;
}
*

char	*get_exec_path(char **path, char *cmd)
{
	char	*slashpath;
	char	*execpath;

	execpath = NULL;
	slashpath = NULL;
	while (*path)
	{
		slashpath = ft_strjoin(*path, "/");
		execpath = ft_strjoin(slashpath, cmd);
		if (access(execpath, X_OK) != -1)
			return (execpath);
		else
		{
			if (execpath)
				free(execpath);
			execpath = NULL;
		}
		path++;
	}
	if (!path)
		return (cmd);
	return (NULL);
}

int	wait_for(int *children)
{
	int	status;
	int	nc;

	nc = 0;
	while (children[nc])
	{
		waitpid(children[nc], &status, 0);
		nc++;
	}
	return (WEXITSTATUS(status));
}

void	free_args(char **args)
{
	int	i;

	if (!args || !*args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
	free(args);
	args = NULL;
}