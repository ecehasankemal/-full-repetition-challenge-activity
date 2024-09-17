#include <unistd.h>

void
    my_putchar(char c)
{
    write(1, &c, 1);
}
void
    my_putstr_non_printable(char *str)
{
    while (*str)
    {
        if (*str < 32 || *str >= 127)
        {
            my_putchar('\\');
            my_putchar("0123456789abcdef"[*str / 16]);
            my_putchar("0123456789abcdef"[*str % 16]);
        }
        else
            my_putchar(*str);
        str++;
    }
}