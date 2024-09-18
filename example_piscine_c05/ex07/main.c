#include <stdio.h>

int my_find_next_prime(int nb);


int
    main(void)
{
    int nb;
    int result;

    nb = 8;
    result = my_find_next_prime(nb);
    printf("The next prime number after %d is %d\n", nb, result);
    return (0);
}