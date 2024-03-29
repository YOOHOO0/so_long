# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seoshin <seoshin@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 17:05:34 by seoshin           #+#    #+#              #
#    Updated: 2023/01/19 17:37:10 by seoshin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

MLX_FLAGS	=	-lmlx -framework OpenGL -framework AppKit

SRCS		=	main.c queue.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
				util_init.c util_key_hook_1.c util_key_hook_2.c util_map.c util_print_or_destroy.c \
				util_free.c util_others.c

OBJS		=	$(SRCS:.c=.o)

NAME		=	so_long

all			:	$(NAME)

$(NAME) 	:	$(OBJS)
				$(CC) $(CFLAGS) $(MLX_FLAGS) $(SRCS) -o so_long

%.o			:	%.c
				$(CC) $(CFLAGS) -c $< -o $@

clean		:
				rm -f $(OBJS)

fclean		:	clean
				rm -f $(NAME)

re			:	fclean
				make all

.PHONY		:	all clean fclean re