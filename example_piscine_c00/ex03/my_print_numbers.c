#include <unistd.h>

void
    my_print_numbers(void)
{
    char c;

    c = '0';
    while (c <= '9')
    {
        write(1, &c, 1);
        c++;
    }
    write(1, "\n", 1);
}