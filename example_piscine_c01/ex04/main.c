#include <stdio.h>

void my_ultimate_div_mod(int *a, int *b);

int
    main(void)
{
    int a = 42;
    int b = 21;

    printf("a: %d, b: %d\n", a, b);
    my_ultimate_div_mod(&a, &b);
    printf("a: %d, b: %d\n", a, b);
    return (0);
}