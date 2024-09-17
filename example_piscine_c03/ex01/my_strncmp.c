int
    my_strncmp(char const *s1, char const *s2, int n)
{
    while (n-- && *s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}