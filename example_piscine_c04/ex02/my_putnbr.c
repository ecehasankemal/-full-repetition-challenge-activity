#include <unistd.h>

void
    my_putnbr(int nb)
{
    long   n;

    n = nb;
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n >= 10)
    {
        my_putnbr(n / 10);
        my_putnbr(n % 10);
    }
    else
    {
        n += '0';
        write(1, &n, 1);
    }

    return ;
}