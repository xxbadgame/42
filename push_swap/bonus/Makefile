CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = 	checker.c \
		$(wildcard rules/*.c) \
		$(wildcard get_next_line/*.c) \
		libft/ft_atoi.c \
		libft/ft_strtrim.c \
		libft/ft_strncmp.c \
		libft/ft_strlen.c \

OBJS = $(SRCS:.c=.o)
NAME = checker
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