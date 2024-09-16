#include <unistd.h>

void
     my_print_alphabet(void)
{
    char c;

    c = 'a';
    while (c <= 'z')
    {
        write(1, &c, 1);
        c++;
    }
    write(1, "\n", 1);
}