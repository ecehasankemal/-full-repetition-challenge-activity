#include <stdio.h>

void    my_swap(int *a, int *b);

int
    main(void)
{
    int a;
    int b;

    a = 42;
    b = 24;
    printf("Before = a: %d\n", a);

    printf("Before = b: %d\n", b);
    
    my_swap(&a, &b);

    printf("After = a: %d\n", a);

    printf("After = b: %d\n", b);
    
    return (0);
}