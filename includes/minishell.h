/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:05:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/30 12:16:19 by ahamalai         ###   ########.fr       */
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
	ROOT,
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

typedef struct s_shell
{
	char	**ms_envp; // Our copy of envp, can be modified by builtins
	char	*input;	// User input line
	t_cmdn	*root; // Root node of command tree, for freeing
	char	**cmdarr; // Array of commands, for easy freeing
	int		pfd[2]; // Pipe file descriptors
	int		efd[2]; // Pipe for env export returns
	char	**cmd; // Most recent expanded cmdarr member
	int		*hdocs;	// Heredoc array for above most recentcmd
	int 	status; // Exit code of the most recent pipe, implement!
}	t_shell;

// Parser:
void		parse_input(t_shell *sh);
// Executor:
int			run_cmds(t_shell *sh);
// Dynamic Integer Array:
t_intvec*	create_intvec(void);
void		expand_intvec(t_intvec *dynarr);
int			add_to_intvec(t_intvec *dynarr, int value);
void		free_intvec(t_intvec *intvec);
// Utilities:
char		**ft_remove_quotes(char **cmd);
char		*get_exec_path(char **path, char *cmd);
int			wait_for(t_intvec *children);
void		print_cmdn(t_cmdn *root);
// char		*trim_string(char *str);
// Buildins:
int			pwd_builtin(void);
int			cd_builtin(char *cwd, char **str);
void		exit_builtin(t_shell *sh);
int			echo_builtin(char **arg);
int			export_builtin(t_cmdn *node, t_shell *sh);
int			env_builtin(t_shell *sh);
int			export_builtin(t_cmdn *node, t_shell *sh);
// Environment variables:
char 		*replace_envp(char* input, t_shell *sh);
char		**copy_envp(char **envp);
char		*move_ucase(char *start);
void		populate_env_vars(t_cmdn *node, t_shell *sh);
// Heredoc:
char		*ft_heredoc(char *breakchar, int hdocs);
// Error handling:
void		errexit(char *msg1, char *msg2, t_shell *sh, int exitcode);
// Initialization and freeing
void		init_shell_struct(t_shell *sh);
void		free_args(char **args);
void		free_cmdn(t_cmdn *node);
void		free_new_prompt(t_shell *sh);
// Signals
void		disable_raw_mode(struct termios oterm);
void		enable_raw_mode(void);

#endif