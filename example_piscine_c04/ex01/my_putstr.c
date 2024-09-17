#include <unistd.h>

void
    my_putstr(char const *str)
{
    while (*str)
        write(1, str++, 1);
}