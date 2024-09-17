#include <stdio.h>

char *my_strlowcase(char *str);

int
    main(void)
{
    char str[] = "HelloWorld";
    printf("%s\n", str);
    printf("%s\n", my_strlowcase(str));
    return (0);
}