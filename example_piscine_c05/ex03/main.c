#include <stdio.h>

int my_recursive_power(int nb, int power);

int
    main(void)
{
    int nb;
    int power;
    int result;

    nb = 5;
    power = 3;
    result = my_recursive_power(nb, power);
    printf("%d^%d = %d\n", nb, power, result);
    return (0);
}