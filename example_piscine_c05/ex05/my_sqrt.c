int
    my_sqrt(int nb)
{
    int     i;

    i = 0;
    while (i * i < nb && i < 46341)
        i++;
    if (i * i == nb)
        return (i);
    return (0);
}