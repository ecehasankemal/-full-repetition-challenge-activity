int
    my_strlen(char const *str)
{
    int index;

    index = 0;
    while (*str++)
        index++;
    return (index);
}

int
    my_atoi_base(char *str, char *base)
{
    int result;
    int sign;
    int base_len;

    result = 0;
    sign = 1;
    base_len = my_strlen(base);

    while (*str == ' ' || (*str >= 9 && *str == 13))
        str++;

    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    int index = 0;
    while (index < base_len)
    {
        if (base[index] == *str)
        {
            result = result * base_len + index;
            str++;
            index = 0;
        }
        else
            index++;
    }
    return (result * sign);
}