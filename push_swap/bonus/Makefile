# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/16 15:30:51 by ynzue-es          #+#    #+#              #
#    Updated: 2025/01/16 15:30:53 by ynzue-es         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	checker.c \
		error_checker.c \
		push_swap_stacks.c \
		rules/push.c \
		rules/reverse_rotate.c \
		rules/rotate.c \
		rules/swap.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		libft/ft_atol.c \
		libft/ft_split.c \
		libft/ft_strtrim.c \
		libft/ft_strncmp.c \
		libft/ft_strlen.c \
		libft/ft_isdigit.c \

OBJS = $(SRCS:.c=.o)
NAME = ../checker
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

re: fclean all

.PHONY: all clean fclean re