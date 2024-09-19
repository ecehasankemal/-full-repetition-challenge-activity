void
    my_sort_string_tab(char **tab)
{
    int     index;
    int     is_sort;
    char    *temp;

    is_sort = 0;
    while (!is_sort)
    {
        is_sort = 1;
        index = 0;
        while (tab[index + 1])
        {
            if (tab[index][0] > tab[index + 1][0] > 0)
            {
                temp = tab[index];
                tab[index] = tab[index + 1];
                tab[index + 1] = temp;
                is_sort = 0;
            }
            index++;
        }
    }
}