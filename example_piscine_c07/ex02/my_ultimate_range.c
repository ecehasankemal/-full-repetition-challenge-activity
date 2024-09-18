#include <stdlib.h>

int
    my_ultimate_range(int **range, int min, int max)
{
    int *result;
    int index;

    if (min >= max)
    {
        *range = NULL;
        return (-1);
    }
    result = (int *)malloc(sizeof(int) * (max - min));
    if (result == NULL)
    {
        *range = NULL;
        return (-1);
    }
    index = 0;
    while (min < max)
        result[index++] = min++;
    *range = result;
    return (index);
}