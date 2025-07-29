# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/29 12:24:55 by yannis            #+#    #+#              #
#    Updated: 2025/07/29 13:48:27 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = src/main.c \
		src/destroy.c \
		src/init.c \
		src/forks.c \
		src/utils.c \
		src/start.c \
		src/routine.c \
		src/end.c \
		libft/ft_atoi.c \
		libft/ft_putendl_fd.c \
		libft/ft_putchar_fd.c \
		libft/ft_isdigit.c \
		

HEADER = inc/philo.h

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -I./inc
RM = rm -rf

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

all : 
	make $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean :
	make clean
	$(RM) $(NAME)

re : fclean
	make all

.PHONY : all clean fclean re
