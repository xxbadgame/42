# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yannis <yannis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 12:30:12 by yannis            #+#    #+#              #
#    Updated: 2025/03/19 17:47:00 by yannis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	src/forks.c \
		src/main.c \
		src/philosophe.c \
		src/monitor.c \
		src/routine.c \
		src/monitor_utils.c \
		src/utils.c \
		libft/ft_atoi.c \

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