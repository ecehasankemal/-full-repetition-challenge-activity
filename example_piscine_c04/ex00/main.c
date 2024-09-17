#include <stdio.h>

int my_strlen(char const *str);

int
    main(void)
{
    char const str[] = "Hello, World!";
    int len;

    len = my_strlen(str);
    printf("Length of string \"%s\" is %d\n", str, len);
    return (0);
}