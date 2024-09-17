void
    my_sort_int_tab(int *tab, int size)
{
    int i = 0;
    int j;
    int temp;

    while (i < size)
    {
        j = 0;
        while (j < size -1)
        {
            if (tab[j] > tab[j + 1])
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}