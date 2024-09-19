#include <stdlib.h>

int
    *my_map(int *tab, int length, int(*f)(int))
{
    int index;
    int *new_tab;

    new_tab = malloc(sizeof(int) * length);
    if (new_tab == NULL)
        return (NULL);
    index = 0;
    while (index < length)
    {
        new_tab[index] = (*f)(tab[index]);
        index++;
    }
    return (new_tab);
}