/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:05:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/11 12:10:31 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include "../libft/libft.h"

#define INITIAL_SIZE 10

typedef enum s_ntype
{
	PIPELINE,
	COMMAND,
	ARGUMENTS,
	REDIRECTIONS
}	t_ntype;	

typedef struct s_cmdn
{
	t_ntype			ntype;
	struct s_cmdn	*left;
	struct s_cmdn	*right;
	char			**cargs;
	char			**envp;
}	t_cmdn;	

typedef struct s_dynint
{
    int		*array;
    size_t	size;
    size_t	capacity;
} t_dynint;

// Parser:
void		parse_input(char *input, t_cmdn **root);
t_cmdn		*init_cmd_node(t_ntype type, char **cmd);
void		print_cmdn(t_cmdn *root);
// Executor:
int			run_cmds(t_cmdn *root);
// Dynamic Integer Array:
t_dynint*	create_dynamic_int_array(void);
void		expand_dynamic_int_array(t_dynint *dynarr);
int			add_to_dynamic_int_array(t_dynint *dynarr, int value);
// Utilities:
char		*get_exec_path(char **path, char *cmd);
void		free_args(char **args);
int			wait_for(t_dynint *children);
char		*trim_string(char *str);


/*
typedef enum s_ntype {
	ROOT,
	CMD,
	PARAM,
	INFILE,
	OUTFILE,
	SPAREN,
	DPAREN
}	t_ntype;

typedef struct s_cmdn {
  t_ntype		ntype;
  char			*symbol;
  struct t_cmdn	*children[NUM_CHILDREN];
} t_cmdn;
*/

void	pwd_builtin(void);
void	cd_builtin(char *cwd, char **str);
void	exit_builtin(void);
void	echo_builtin(char **arg);

#endif