# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 00:28:51 by yannis            #+#    #+#              #
#    Updated: 2025/02/17 11:03:22 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L/usr/lib -lX11 -lXext -lm
SRCS = 	src/main.c \
		src/fdf_utils.c \
		src/fdf_utils2.c \
		src/parsing.c \
		src/points.c \
		src/segment.c \
		src/create_lines.c \
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
MLX = libmlx.a
HEADER = fdf.h
GNL_HEADER = get_next_line/get_next_line.h
LIBFT_HEADER = libft/libft.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(MLXFLAGS) -I$(HEADER) -I$(GNL_HEADER) -I$(LIBFT_HEADER)

%.o : %.c $(HEADER) $(GNL_HEADER) $(LIBFT_HEADER) $(MLX) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re