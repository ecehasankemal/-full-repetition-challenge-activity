#include <stdio.h>

int my_ultimate_range(int **range, int min, int max);

int
    main(void)
{
    int **range;
    int *result;
    int current;

    range = &result;
    current = my_ultimate_range(range, 5, 10);
    if (current == -1)
    {
        printf("An error occurred\n");
        return (1);
    }
    for (int i = 0; i < 5; i++)
        printf("%d\n", result[i]);

    printf("---Current: %d\n", current);
    return (0);
}