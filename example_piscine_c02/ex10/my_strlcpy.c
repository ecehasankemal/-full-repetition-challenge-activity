int
    my_strlen(const char *str)
{
    int count;

    count = 0;
    while (*str)
    {
        str++;
        count++;
    }
    return (count);
}

unsigned int
    my_strlcpy(char *dest, char *src, unsigned int size)
{
    if (size == 0)
        return (my_strlen(src));
    
    unsigned int index;

    index = 0;
    while (src[index] && index < size - 1)
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return (my_strlen(src));
}