int
    my_atoi(char const *str)
{
    int result;
    int sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str == 13))
        str++;
    while (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + *str - '0';
        str++;
    }
    return (result * sign);
}