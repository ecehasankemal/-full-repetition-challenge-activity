#include <stdio.h>

void my_swap(int *a, int *b);

int
    main(void)
{
    int a = 21;
    int b = 42;

    printf("a: %d, b: %d\n", a, b);
    my_swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);
    return (0);
}