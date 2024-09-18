int
    my_strlen(char *str)
{
    int i;

    i = 0;
    while (*str++)
        i++;
    return (i);
}