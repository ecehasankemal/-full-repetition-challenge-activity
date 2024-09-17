char
    *my_strncat(char *dest, char const *src, unsigned int nb)
{
    char *ptr = dest;
    while (*ptr)
        ptr++;
    while (*src && nb--)
    {
        *ptr = *src;
        src++;
        ptr++;
    }
    *ptr = '\0';
    return (dest);
}