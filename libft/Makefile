# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 12:03:42 by ahamalai          #+#    #+#              #
#    Updated: 2024/05/27 11:17:51 by ahamalai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	libft.a
CC 				=	cc 
CFLAGS 			=	-Wall -Wextra -Werror -g -O0 -I
DEBUG_FLAGS 	=	-g -O0
# -O0 -fsanitize=address
SRCS 			=   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	        		ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	            	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	            	ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	            	ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	            	ft_atoi.c ft_calloc.c ft_strdup.c ft_putchar_fd.c \
	            	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	            	ft_strjoin.c ft_substr.c ft_strtrim.c ft_itoa.c \
	            	ft_split.c ft_striteri.c ft_strmapi.c get_next_line.c \
	            	get_next_line_utils.c ft_printf.c ft_printhex.c \
	            	ft_split_time_space_utils.c ft_split_time_space.c \
	            	ft_strcpos.c ft_isspace.c quote_check.c \

SRC_DIR			= 	./srcs
OBJ_DIR			=	./objs
INCLUDE			=  	./incs
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

all				: 	$(NAME)

$(NAME) 		: 	$(OBJS) | $(OBJ_DIR)
					@ar -crs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o  :	$(SRC_DIR)/%.c | $(OBJ_DIR)
					$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)

debug			:	CFLAGS += $(DEBUG_FLAGS)
debug			:	all

clean 			: 
					@rm -rf $(OBJ_DIR)

fclean 			:	clean 
					@rm -f $(NAME)

re 				:	fclean all

.PHONY 			:	all clean fclean re debug
