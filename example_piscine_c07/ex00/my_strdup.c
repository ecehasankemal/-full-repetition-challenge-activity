#include <stdlib.h>

int
    my_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

char 
    *my_strdup(char *src)
{
    char *result;
    int     len;

    len = my_strlen(src);
    result = (char *)malloc(sizeof(char) * len) + 1;
    if (result == NULL)
        return (NULL);
    while (*src)
        *result++ = *src++;
    *result = '\0';
    return (result - len);
}