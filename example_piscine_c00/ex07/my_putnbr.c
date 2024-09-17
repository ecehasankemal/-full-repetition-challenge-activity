#include <unistd.h>

void
    my_putchar(char c)
{
    write(1, &c, 1);
}

void
    my_putnbr(int n)
{
    long    nbr;

    nbr = n;
    if (nbr < 0)
    {
        my_putchar('-');
        my_putnbr(-nbr);
    }
    else if (nbr >= 10)
    {
        my_putnbr(nbr / 10);
        my_putnbr(nbr % 10);
    }
    else
    {
        my_putchar(nbr + '0');
    }
}
