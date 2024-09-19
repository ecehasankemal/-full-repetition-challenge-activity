SRCS = main.c my_display_file.c

OBJS = $(SRCS:.c=.o)

SRC_DIR = srcs
INC_DIR = inc
OBJ_DIR = objs

CFLAGS = -Wall -Wextra -Werror

NAME = my_display_file

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJS))
	gcc $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(addprefix $(OBJ_DIR)/, $(OBJS))

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
