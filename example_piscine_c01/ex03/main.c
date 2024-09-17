#include <stdio.h>

void my_div_mod(int a, int b, int *div, int *mod);

int
    main(void)
{
    int a = 42;
    int b = 21;
    int div = 0;
    int mod = 0;

    printf("a: %d, b: %d, div: %d, mod: %d\n", a, b, div, mod);
    my_div_mod(a, b, &div, &mod);
    printf("a: %d, b: %d, div: %d, mod: %d\n", a, b, div, mod);
    return (0);
}