gcc -Wall -Wextra -Werror -c my_putchar.c my_swap.c my_putstr.c my_strlen.c my_strcmp.c
ar rc libmy.a my_putchar.o my_swap.o my_putstr.o my_strlen.o my_strcmp.o
ranlib libmy.a