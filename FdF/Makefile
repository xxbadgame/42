# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 00:28:51 by yannis            #+#    #+#              #
#    Updated: 2025/01/19 20:33:23 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	fdf.c \
		fdf_utils.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		libft/ft_strlen.c \
		libft/ft_atoi.c \
		libft/ft_split.c \
		libft/ft_strchr.c \
		libft/ft_substr.c \
		
OBJS = $(SRCS:.c=.o)
MLX = minilibx/libmlx.a
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) minilibx/libmlx.a -L/usr/lib -lX11 -lXext -lm

%.o : %.C
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re