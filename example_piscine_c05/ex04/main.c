#include <stdio.h>


int my_fibonacci(int index);

int
    main(void)
{
    int index;
    int result;

    index = 7;
    result = my_fibonacci(index);
    printf("Fibonacci index %d = %d\n", index, result);
    return (0);
}