int
    my_str_is_uppercase(char *str)
{
    int count;

    count = 0;
    while (str[count])
    {
        if (!(str[count] >= 'A' && str[count] <= 'Z'))
            return (0);
        count++;
    }
    return (1);
}