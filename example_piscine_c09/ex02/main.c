#include <stdio.h>

char **my_split(char *str, char *charset);

int
    main(void)
{
    char *str = "Hello, World!";
    char *charset = ", ";
    char **result = my_split(str, charset);
    for (int i = 0; result[i]; i++)
        printf("%s\n", result[i]);
    return (0);
}