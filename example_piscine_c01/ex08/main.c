#include <stdio.h>

void    my_sort_int_tab(int *tab, int size);

int
    main(void)
{
    int arr[5] = {5, 3, 4, 2, 1};
    
    int i = 0;
    while (i < 5)
    {
        printf("%d", arr[i]);
        i++;
    }
    printf("\n");
    my_sort_int_tab(arr, 5);
    i = 0;
    while (i < 5)
    {
        printf("%d", arr[i]);
        i++;
    }
    printf("\n");
    return (0);
}