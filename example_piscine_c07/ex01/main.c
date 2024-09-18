#include <stdio.h>

int *my_range(int min, int max);

int main(void)
{
    int *range = my_range(5, 10);
    int i = 0;
    while (i < 5)
        printf("%d\n", range[i++]);
    return (0);
}