int
    my_strlen(char const *str)
{
    int len = 0;
    while (*str)
    {
        str++;
        len++;
    }
    return (len);
}

unsigned int
    my_strlcat(char *dest, char const *src, unsigned int size)
{
    char            *ptr = dest;
    unsigned int    dest_len = 0;
    unsigned int    src_len = 0;

    while (*ptr && dest_len < size)
    {
        ptr++;
        dest_len++;
    }
    if (dest_len == size)
        return (dest_len + my_strlen(src));

    while (*src && dest_len + 1 < size)
    {
        *ptr = *src;
        ptr++;
        src++;
        dest_len++;
    }
    *ptr = '\0';
    while (*src)
    {
        src++;
        src_len++;
    }
        return (dest_len + src_len);
}

/*
    isteyenler için alttakide de kısa hali ve kullanılabilir


unsigned int
    my_strlcat(char *dest, char const *src, unsigned int size)
    {
        char    *ptr = dest;
        unsigned int    i = 0;
        while (*ptr && i < size)
        {
            ptr++;
            i++;
        }
        while (*src && i + 1 < size)
        {
            *ptr = *src;
            ptr++;
            src++;
            i++;
        }
        if (i < size)
            *ptr = '\0';
        while (*src)
        {
            src++;
            i++;
        }
        return (i);
    }
*/