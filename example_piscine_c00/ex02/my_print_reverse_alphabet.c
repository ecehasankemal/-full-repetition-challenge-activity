#include <unistd.h>

void
    my_print_reverse_alphabet(void)
{
    char c;

    c = 'z';
    while (c >= 'a')
    {
        write(1, &c, 1);
        c--;
    }
    write(1, "\n", 1);
}