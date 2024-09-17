int my_atoi(char const *str);

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

int
    main(void)
{
    int result;

    result = my_atoi(" ---+--+1234ab567");
    my_putnbr(result);
    write(1, "\n", 1);
    return (0);
}