char
    *my_strcat(char *dest, char const *src)
{
    char *ptr = dest;
    while (*ptr)
        ptr++;
    while (*src)
    {
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';
    return (dest);
}