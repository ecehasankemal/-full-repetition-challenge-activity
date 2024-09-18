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
    *my_strjoin(int size, char **strs, char *sep)
{
    int    len;
    int     index;
    int     current;
    char    *result;
    char    *res_ptr;
    char    *str_ptr;
    char    *sep_ptr;

    index = 0;
    len = 0;
    current = 0;
    while (index < size)
        len += my_strlen(strs[index++]);
    len += my_strlen(sep) * (size - 1);
    result = (char *)malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return (NULL);
    
    index = 0;
    res_ptr = result;
    while (current < size)
    {
        str_ptr = strs[current];
        while (*str_ptr)
            *res_ptr++ = *str_ptr++;
        if (current + 1 < size)
        {
            sep_ptr = sep;
            while (*sep_ptr)
                *res_ptr++ = *sep_ptr++;
        }
        current++;
    }
    *res_ptr = '\0';
    return (result);
}
        

    // pointer deği kullanıcam
    // strs[0] = kemal
    // strs[1] = kurt
    // strs[2] = anlamak
    // sep[0] = "; "

    // sonuç = "kemal; kurt; anlamak"
