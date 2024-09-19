int
    my_is_sort(int *tab, int length, int(*f)(int, int))
{
    int     index;
    int     is_sort;

    index = 0;
    is_sort = 1;
    while (index < length - 1)
    {
        if (f(tab[index], tab[index + 1]) > 0)
        {
            is_sort = 0;
            break;
        }
        index++;
    }
    return is_sort;
}