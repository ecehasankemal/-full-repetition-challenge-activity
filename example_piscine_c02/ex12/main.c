#include <stdio.h>

void    my_print_memory(void *addr, unsigned int size);

int
    main(void)
{
    char *str;

    str = "Bonjour les amin";
    my_print_memory(str, 16);
    return (0);
}