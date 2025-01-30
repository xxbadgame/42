# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 00:28:51 by yannis            #+#    #+#              #
#    Updated: 2025/01/30 12:04:38 by ynzue-es         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	fdf.c \
		fdf_utils.c \
		parsing.c \
		free.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		libft/ft_strlen.c \
		libft/ft_atoi.c \
		libft/ft_split.c \
		libft/ft_strchr.c \
		libft/ft_substr.c \
		libft/ft_putchar_fd.c \
		libft/ft_putendl_fd.c \
		
OBJS = $(SRCS:.c=.o)
MLX = minilibx/libmlx.a
HEADER = fdf.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) minilibx/libmlx.a -L/usr/lib -lX11 -lXext -lm

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re