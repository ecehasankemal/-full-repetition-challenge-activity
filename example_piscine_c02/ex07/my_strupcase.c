char
    *my_strupcase(char *str)
{
    int count;

    count = 0;
    while (str[count])
    {
        if (str[count] >= 'a' && str[count] <= 'z')
            str[count] -= 32;
        count++;
    }
    return (str);
}