char
    *my_strlowcase(char *str)
{
    int count;
    
    count = 0;
    while (str[count])
    {
        if (str[count] >= 'A' && str[count] <= 'Z')
            str[count] += 32;
        count++;
    }
    return (str);
}