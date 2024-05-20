# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:36:32 by ahamalai          #+#    #+#              #
#    Updated: 2024/05/20 07:05:06 by mburakow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	minishell
CC 				=	cc
CFLAGS 			=	-Wall -Wextra -Werror -g -O0 -I ~/.brew/opt/readline/include
DEBUG_FLAGS 	=	-g -O0
# -O0 -fsanitize=address
SRC_DIR			=	./srcs
INC_DIRS		=	./incs ./libft/incs
INCLUDE 		=	$(foreach dir, $(INC_DIRS), -I $(dir))
MAKE 			=	make
SRCS 			=	main.c builtins.c parser.c executor.c utils.c intvec.c \
                    msenv.c msenv_replace.c msenv_modify.c heredoc.c error.c \
					free.c redirect.c init.c 
OBJ_DIR			=	./objs
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all : 				$(NAME)

debug: 				CFLAGS += $(DEBUG_FLAGS)
debug:				all

$(NAME):			$(LIBFT) $(OBJ_DIR) $(OBJS)
					$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib

$(LIBFT):
					make -C $(LIBFT_DIR) all

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					@$(MAKE) -C $(LIBFT_DIR) clean
					rm -rf $(OBJ_DIR)

fclean:				
					@$(MAKE) -C $(LIBFT_DIR) fclean
					rm -rf $(OBJ_DIR)
					rm -f $(NAME)

re:					fclean all

.PHONY: 			all clean fclean re bonus libft
