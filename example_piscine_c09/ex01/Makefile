SRC = my_swap.c my_putchar.c my_putstr.c my_strlen.c my_strcmp.c

SRC_DIR = src/

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = libmy.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

