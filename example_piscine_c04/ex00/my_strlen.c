int
    my_strlen(char const *str)
{
    int index;

    index = 0;
    while (*str++)
        index++;
    return (index);
}