/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:05:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/20 15:09:02 by mburakow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>

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
	char			**cargs;
	int				*hdocs;
	int				*redirs;
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
	// int		sfd[2]; // Pipe for status code returns
	char	**cmd; // Most recent expanded cmdarr member
	int		*hdocs;	// Heredoc array for above most recent cmd
	t_bool	hdoc;
	int		*redirs; // Redirect array for all redirects of most recent cmd
	int 	status; // Exit code of the most recent pipe, implement!
	int		cmdcount;
	struct termios	oterm;
}	t_shell;

// Parser:
void		parse_input(t_shell *sh);
// Executor:
int			run_cmds(t_shell *sh);
void		modify_status(t_shell *sh);
// Dynamic Integer Array:
t_intvec*	create_intvec(t_shell *sh);
void		expand_intvec(t_intvec *dynarr, t_shell *sh);
int			add_to_intvec(t_intvec *dynarr, int value, t_shell *sh);
void		free_intvec(t_intvec *intvec);
// Utilities:
char		**ft_remove_quotes(char **cmd);
char		*get_exec_path(char **path, char *cmd, t_shell *sh);
int			wait_for(t_intvec *children);
void		print_cmdn(t_cmdn *root);
char		*trim_string(char *str);
void		create_pipes(t_shell *sh);
// Buildins:
int			pwd_builtin(t_shell *sh);
int			cd_builtin(t_cmdn *node, t_shell *sh, char	*cwd);
void		exit_in_main(t_cmdn *node, t_shell *sh);
int			echo_builtin(char **arg);
int			env_builtin(t_shell *sh, t_bool export);
int			export_builtin(t_cmdn *node, t_shell *sh);
int			unset_builtin(t_cmdn *node, t_shell *sh);
char		**remove_array(t_shell *sh, char **temp_ms);
// Environment variables:
char 		*replace_envp(char* input, t_shell *sh);
char		**copy_envp(char **envp, t_shell *sh);
char		*move_ucase(char *start);
void		populate_env_vars(t_cmdn *node, t_shell *sh);
void		modify_env_internal(char *name, char *value, t_shell *sh);
char		*get_env_val_by_name(char *name, t_shell *sh);
// Heredoc:
char		*ft_heredoc(char *breakchar, int hdocs);
// Redirects:
char 		*trim_rdirspace(char *cmd);
void		get_redirects(t_shell *sh);
int			open_redirects(t_cmdn *node, t_shell *sh);
// Error handling:
void		errexit(char *msg1, char *msg2, char *msg3, t_shell *sh);
void		errexitcode(char *msg1, char *msg2, int status, t_shell *sh);
// Initialization
void		init_shell_struct(t_shell *sh);
t_cmdn		*init_cmd_node(t_ntype type, t_shell *sh, t_bool last);
// Freeing
void 		free(void* p);
void		free_args(char **args);
void		free_cmdn(t_cmdn *node);
void		free_child(t_shell *sh);
void		free_new_prompt(t_shell *sh);
void		close_all_pipes(t_shell *sh);
// Signals
void		disable_raw_mode(struct termios oterm);
void		enable_raw_mode(void);

#endif