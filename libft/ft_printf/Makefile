# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mburakow <mburakow@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 20:09:48 by mburakow          #+#    #+#              #
#    Updated: 2023/12/18 11:14:27 by mburakow         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -I
SRC_DIR			= 	srcs
INCLUDE			= 	incs
SRCS			= 	ft_printf.c			ft_print_addr.c		ft_print_char.c	\
					ft_print_string.c	ft_print_hex.c		ft_print_uint.c	\
					ft_print_int.c
OBJ_DIR			=	objs
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
LIBFT_DIR		=	./libft
LIBFT			=	$(LIBFT_DIR)/libft.a

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all:				$(NAME)

bonus:				all

$(NAME):			$(LIBFT) $(OBJ_DIR) $(OBJS)
					cp	$(LIBFT) $(NAME)
					ar -crs $(NAME) $(OBJS)

$(LIBFT):
					make -C $(LIBFT_DIR) all

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					make -C $(LIBFT_DIR) clean
					rm -rf $(OBJ_DIR)

fclean:				clean
					make -C $(LIBFT_DIR) fclean
					rm -f $(NAME)
					rm -f $(LIBFT)

re:					fclean all

.PHONY:				all bonus clean fclean re libft
