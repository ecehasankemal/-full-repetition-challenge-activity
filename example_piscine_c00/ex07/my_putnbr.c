#include <unistd.h>

void
    my_putchar(char c)
{
    write(1, &c, 1);
}

void
    my_putnbr(int n)
{
    if (n < 0)
    {
        my_putchar('-');
        my_putnbr(-n);
    }
    else if (n >= 10)
    {
        my_putnbr(n / 10);
        my_putnbr(n % 10);
    }
    else
    {
        my_putchar(n + '0');
    }
}