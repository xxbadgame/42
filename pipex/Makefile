# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 22:58:20 by yannis            #+#    #+#              #
#    Updated: 2025/01/19 09:59:14 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs

SRCS = 	pipex.c \
		pipex_utils.c \
		pipex_utils2.c \
		libft/ft_strlcat.c \
		libft/ft_strlcpy.c \
		libft/ft_strlen.c \
		libft/ft_split.c \
		libft/ft_strncmp.c \
		libft/ft_strtrim.c \
		libft/ft_strdup.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.o=.c)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re



