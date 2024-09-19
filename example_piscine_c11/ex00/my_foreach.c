void
    my_foreach(int *tab, int length, void(*f)(int))
{
    int i;

    i = 0;
    while (i < length)
    {
        f(tab[i]);
        i++;
    }
}