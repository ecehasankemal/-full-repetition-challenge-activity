#include <unistd.h>

void
    my_putstr(char const *str)
{
    while (*str != '\0')
    {
        write(1, str, 1);
        str++;
    }
}