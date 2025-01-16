# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynzue-es <ynzue-es@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/21 15:32:57 by yannis            #+#    #+#              #
#    Updated: 2025/01/16 15:18:45 by ynzue-es         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	push_swap.c \
		push_swap_utils.c \
		push_swap_stacks.c \
		sort_three.c \
		cost_push.c \
		rotation.c \
		error_checker.c \
		libft/ft_atol.c \
		libft/ft_split.c \
		libft/ft_strlen.c \
		libft/ft_isdigit.c \
		libft/ft_strtrim.c \
		rules/push.c \
		rules/reverse_rotate.c \
		rules/rotate.c \
		rules/swap.c \

OBJS = $(SRCS:.c=.o)
NAME = push_swap
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