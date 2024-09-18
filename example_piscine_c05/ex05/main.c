#include <stdio.h>

int my_sqrt(int nb);

int
    main(void)
{
    int nb;
    int result;

    nb = 25;
    result = my_sqrt(nb);
    printf("Square root of %d = %d\n", nb, result);
    return (0);
}