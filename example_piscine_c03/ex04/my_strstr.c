char
    *my_strstr(char *str, char const *to_find)
{
    if (!*to_find)
        return (str);
    while (*str)
    {
        char *ptr = str;
        char const *to_find_ptr = to_find;
        while (*ptr && *to_find_ptr && *ptr == *to_find_ptr)
        {
            ptr++;
            to_find_ptr++;
        }
        if (!*to_find_ptr)
            return (str);
        str++;
    }
    return ((char *)0);
}