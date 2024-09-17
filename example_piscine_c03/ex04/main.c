#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strstr(char *str, char const *to_find);

int
    main(void)
{
    char str[] = "Hello World!";
    char const *to_find = "World";
    char *res = my_strstr(str, to_find);
    if (res != NULL)
    {
        char    *dup_res = strdup(res);
        if (dup_res == NULL)
        {
            printf("%s\n", dup_res);
            free (dup_res);
        }
        else
            printf("%s\n", dup_res);
    }
    return (0);
}
