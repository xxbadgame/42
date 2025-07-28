# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 12:30:12 by yannis            #+#    #+#              #
#    Updated: 2025/07/28 17:50:31 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRCS = 	src/main.c \
		src/philo.c \
		src/philo_utils.c \
		src/monitor.c \
		src/utils.c \
		src/forks.c \
		libft/ft_atoi.c \
		libft/ft_putendl_fd.c \
		libft/ft_putchar_fd.c \
		libft/ft_isdigit.c \
		libft/ft_strcmp.c \

OBJSDIR = src/obj
OBJS = $(SRCS:%.c=$(OBJSDIR)/%.o)
HEADER = philosopher.h
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I$(HEADER)

$(OBJSDIR)/%.o: %.c $(HEADER) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re