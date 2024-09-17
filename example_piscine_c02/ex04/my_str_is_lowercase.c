int
    my_str_is_lowercase(char *str)
{
    int count;

    count = 0;
    while (str[count])
    {
        if (!(str[count] >= 'a' && str[count] <= 'z'))
            return (0);
        count++;
    }
    return (1);
}