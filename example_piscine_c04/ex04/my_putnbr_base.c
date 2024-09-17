#include <unistd.h>

void
    my_putnbr_base(int nbr, char *base)
{
    int     base_len;
    long    n;

    base_len = 0;
    while (base[base_len])
        base_len++;
    n = nbr;
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n >= base_len)
    {
        my_putnbr_base(n / base_len, base);
        my_putnbr_base(n % base_len, base);
    }
    else
    {
        n += base[0];
        write(1, &n, 1);
    }

    return ;
}