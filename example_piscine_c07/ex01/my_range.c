#include <stdlib.h>

int
    *my_range(int min, int max)
{
    int *range;
    int index;

    if (min >= max)
        return (NULL);
    range = (int *)malloc(sizeof(int) * (max - min));
    if (range == NULL)
        return (NULL);
    index = 0;
    while (min < max)
        range[index++] = min++;
    return (range);
}

