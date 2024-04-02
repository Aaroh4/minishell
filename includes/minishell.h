/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:05:01 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/02 15:30:23 by mburakow         ###   ########.fr       */
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

# define NUM_CHILDREN 30  

typedef enum s_ntype 
{
	PIPELINE,
	COMMAND,
	ARGUMENTS,
	REDIRECTIONS
}	t_ntype;	

typedef struct s_cmdn 
{
	t_ntype	ntype;
	char	*symbol;
	t_cmdn	*left;
	t_cmdn	*right;
	char	**args;
}	t_cmdn;	

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

void	parse_input(char *input, t_cmdn *croot);
t_cmdn	*init_cmdn(t_ntype type, char *symbol);
void	print_cmdn(t_cmdn *croot);

#endif