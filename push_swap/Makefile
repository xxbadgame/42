CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = push_swap.c push_swap_utils.c sort_three.c cost_push.c rotation.c $(wildcard rules/*.c)
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