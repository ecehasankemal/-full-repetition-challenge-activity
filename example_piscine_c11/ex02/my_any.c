int
    my_any(char **tab, int(*f)(char *))
{
    int     index;

    index = 0;
    while (tab[index])
    {
        if ((*f)(tab[index]))
            return (1);
        index++;
    }
    return (0);
}

