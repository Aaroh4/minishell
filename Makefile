# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:36:32 by ahamalai          #+#    #+#              #
#    Updated: 2024/04/03 16:07:23 by ahamalai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFTDIR = ./libft
MAKE = make
CC = cc
CFLAGS = -Wall -Wextra -Werror -I ~/.brew/opt/readline/include
HEAD = includes/minishell.h
SRCS = main.c builtins.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C $(LIBFTDIR)
		@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib

clean:
		@rm -f $(OBJS)
		@$(MAKE) clean -C $(LIBFTDIR)

fclean: clean
		@rm -f $(NAME)
		@rm -f libft.a
		@$(MAKE) fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re bonus
