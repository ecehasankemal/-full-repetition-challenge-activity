#include <stdio.h>

char *my_strcat(char *dest, char const *src);

int
    main(void)
{
    char dest[50] = "Hello";
    char const *src = " World!";
    printf("%s\n", my_strcat(dest, src));
    return (0);
}