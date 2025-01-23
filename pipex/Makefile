# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 22:58:20 by yannis            #+#    #+#              #
#    Updated: 2025/01/23 12:31:48 by ynzue-es         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = 	pipex.c \
		pipex_free.c \
		pipex_fds.c \
		pipex_cmds.c \
		libft/ft_strlcat.c \
		libft/ft_strlcpy.c \
		libft/ft_strlen.c \
		libft/ft_split.c \
		libft/ft_strncmp.c \
		libft/ft_strtrim.c \
		libft/ft_strdup.c \
		libft/ft_putendl_fd.c \
		libft/ft_putchar_fd.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)
HEADER = pipex.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(HEADER)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re



