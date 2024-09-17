int
    my_str_is_numeric(char *str)
{
    int count;

    count = 0;
    while (str[count])
    {
        if (!(str[count] >= '0' && str[count] <= '9'))
            return (0);
        count++;
    }
    return (1);
}