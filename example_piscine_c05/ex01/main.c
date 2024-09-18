#include <stdio.h>

int my_recursive_factorial(int nb);

int
    main(void)
{
    int nb;
    int result;

    nb = 5;
    result = my_recursive_factorial(nb);
    printf("%d! = %d\n", nb, result);
    return (0);
}