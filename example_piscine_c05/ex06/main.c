#include <stdio.h>

int my_is_prime(int nb);

int
    main(void)
{
    int nb;
    int result;

    nb = 7;
    result = my_is_prime(nb);
    if (result == 1)
        printf("%d is a prime number\n", nb);
    else
        printf("%d is not a prime number\n", nb);
    return (0);
}