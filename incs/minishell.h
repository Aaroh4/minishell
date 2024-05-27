/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:05:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/05/27 10:50:24 by ahamalai         ###   ########.fr       */
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

# define INITIAL_SIZE 10

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
	t_bool			first;
}	t_cmdn;	

typedef struct s_intvec
{
	int		*array;
	size_t	size;
	size_t	capacity;
}	t_intvec;

typedef struct s_shell
{
	char			**ms_envp;
	char			*input;
	t_cmdn			*root;
	char			**cmdarr;
	int				pfd[2][2];
	int				efd[2];
	int				hfd[2];
	char			**cmd;
	int				*hdocs;
	int				*redirs;
	int				status;
	int				cmdcount;
	struct termios	oterm;
}	t_shell;

// Parser:
void		parse_input(t_shell *sh);
// Executor:
int			run_cmds(t_shell *sh);
void		modify_status(t_shell *sh);
void		close_input_pipes(t_shell *sh);
void		close_output_pipes(t_shell *sh);
void		switch_pipe_fds(t_shell *sh);
int			*ft_remove_hdocs(int i, t_cmdn *node);
void		handle_heredocs(t_cmdn *node, t_shell *sh);
int			check_hdocs(t_cmdn *node);
char		*get_msenv(char *name, t_shell *sh);
char		**remove_from_array(char **str, int i, t_cmdn *node);
int			exec_builtin(t_cmdn *node, t_shell *sh, char *cwd);
void		make_child(t_cmdn *node, t_shell *sh,
				t_intvec *commands, char *cwd);
void		clean_cargs_hdrd(t_cmdn *node);
void		exec_cmd(t_cmdn *node, t_shell *sh, char *cwd);
void		check_builtin(t_cmdn *node, t_shell *sh, char *cwd);
// Dynamic Integer Array:
t_intvec*	create_intvec(t_shell *sh);
void		expand_intvec(t_intvec *dynarr, t_shell *sh);
int			add_to_intvec(t_intvec *dynarr, int value, t_shell *sh);
void		free_intvec(t_intvec *intvec);
// Utilities:
char		**remove_quotes_ex_export(char **cmd, t_shell *sh);
char		test_quote_level(char *str);
char		*remove_quote_level(char *str, t_shell *sh);
char		*get_exec_path(char **path, char *cmd, t_shell *sh);
int			wait_for(t_intvec *children);
void		print_cmdn(t_cmdn *root);
char		*trim_string(char *str);
void		create_pipes(t_shell *sh);
void		print_char_array(char **arr);
void		exit_function(void);
void		input_start(t_shell *sh, struct termios oterm);
// Buildins:
int			pwd_builtin(t_shell *sh);
int			cd_builtin(t_cmdn *node, t_shell *sh, char	*cwd);
void		exit_in_main(t_cmdn *node, t_shell *sh);
int			echo_builtin(char **arg);
int			env_builtin(t_shell *sh, t_bool export);
int			export_builtin(t_cmdn *node, t_shell *sh);
int			unset_builtin(t_cmdn *node, t_shell *sh);
int			get_cargs_count(t_cmdn *node);
char		*check_for_home(t_shell *sh);
int			find_amount(char *str, char c);
int			count_array(char **arr);
char		**unset_remove_from_array(t_shell *sh, char **temp_ms);
char		**removing_loop(char *tempstr, char **temp_ms, int *j);

// Environment variables:
void		increase_shell_level(t_shell *sh);
char		*replace_envp_tags(char* input, t_shell *sh);
char		**copy_envp(char **envp, t_shell *sh);
char		*move_ucase(char *start);
void		populate_env_vars(t_cmdn *node, t_shell *sh);
void		modify_env_internal(char *name, char *value, t_shell *sh);
char		*get_env_val_by_name(char *name, t_shell *sh);
void		modify_env(t_shell *sh, int a, char *cwd);
// Heredoc:
char		*ft_heredoc(char *breakchar, int hdocs);
// Redirects:
char		*trim_rdirspace(char *cmd);
void		get_redirects(t_shell *sh);
int			open_redirects(t_cmdn *node, t_shell *sh);
// Error handling:
void		errexit(char *msg1, char *msg2, char *msg3, t_shell *sh);
void		errexitcode(char *msg1, char *msg2, int status, t_shell *sh);
// Initialization
void		init_shell_struct(t_shell *sh);
t_cmdn		*init_cmd_node(t_ntype type,
				t_shell *sh, t_bool last, t_bool first);
// Freeing
void		free(void* p);
void		free_args(char **args);
void		free_cmdn(t_cmdn *node);
void		free_child(t_shell *sh);
void		free_new_prompt(t_shell *sh);
void		close_ext_pipes(t_shell *sh);
// Signals
void		disable_raw_mode(struct termios oterm);
void		enable_raw_mode(void);

#endif