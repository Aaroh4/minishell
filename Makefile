# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/22 12:36:32 by ahamalai          #+#    #+#              #
#    Updated: 2024/05/09 14:34:59 by ahamalai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	minishell
CC 				=	cc
CFLAGS 			=	-Wall -Wextra -Werror -I ~/.brew/opt/readline/include
DEBUG_FLAGS 	=	-fsanitize=address -g
SRC_DIR			=	./srcs
INC_DIRS		=	./incs ./libft/incs
INCLUDE 		=	$(foreach dir, $(INC_DIRS), -I $(dir))
MAKE 			=	make
SRCS 			=	main.c builtins.c parser.c executor.c utils.c intvec.c \
                    msenv.c msenv_replace.c heredoc.c error.c init_free.c \
					redirect.c
OBJ_DIR			=	./objs
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all : 				$(NAME)

debug: 				CFLAGS += $(DEBUG_FLAGS)
debug:				alld

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
