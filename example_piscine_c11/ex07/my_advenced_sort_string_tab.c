int
    cmp(char *a, char *b)
{
    while (*a && *b)
    {
        if (*a != *b)
            return *a - *b;
        a++;
        b++;
    }
    return *a - *b;
}

void
    my_advanced_sort_string_tab(char **tab, int(*cmp)(char *, char *))
{
    int     index;
    int     is_ported;
    char    *temp;

    is_ported = 0;
    while (!is_ported)
    {
        is_ported = 1;
        index = 0;
        while (tab[index + 1])
        {
            if (cmp(tab[index], tab[index + 1]) > 0)
            {
                temp = tab[index];
                tab[index] = tab[index + 1];
                tab[index + 1] = temp;
                is_ported = 0;
            }
            index++;
        }
    }
}