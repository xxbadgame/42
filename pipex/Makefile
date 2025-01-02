# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 22:58:20 by yannis            #+#    #+#              #
#    Updated: 2025/01/02 00:33:33 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a 

CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs

SRCS = 	pipex.c \
		libft/ft_strlcat.c \
		libft/ft_strlen.c \
		libft/ft_strlcpy.c \
		libft/ft_split.c \

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



