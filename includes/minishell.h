/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:05:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/19 13:08:12 by mburakow         ###   ########.fr       */
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

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

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
	char			**cargs; // cargs[i] == "<< END" = "Heredoc text"
	int				*hdocs;
	t_bool			last;
}	t_cmdn;	

typedef struct s_intvec
{
    int		*array;
    size_t	size;
    size_t	capacity;
} t_intvec;

// Parser:
void		parse_input(char *input, t_cmdn **root);
t_cmdn		*init_cmd_node(t_ntype type, char **cmd, t_bool last, int *hdocs);
void		print_cmdn(t_cmdn *root);
// Executor:
int			run_cmds(t_cmdn *root, int *pfd, char **envp);
// Dynamic Integer Array:
t_intvec*	create_intvec(void);
void		expand_intvec(t_intvec *dynarr);
int			add_to_intvec(t_intvec *dynarr, int value);
void		free_intvec(t_intvec *intvec);
// Utilities:
char		*get_exec_path(char **path, char *cmd);
void		free_args(char **args);
void		free_cmdn(t_cmdn *node);
int			wait_for(t_intvec *children);
char		*trim_string(char *str);
// Buildins:
void		pwd_builtin(void);
void		cd_builtin(char *cwd, char **str);
void		exit_builtin(void);
void		echo_builtin(char **arg);
// Environment variables:
char 		*replace_envp(char* input, char **ms_envp, int hdoc);
char		**copy_envp(char **envp);
void		populate_env_vars(t_cmdn *node, char **ms_envp);

#endif