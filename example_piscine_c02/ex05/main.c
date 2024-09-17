#include <stdio.h>

int my_str_is_uppercase(char *str);

int
    main(void)
{
    char str[] = "HELLO";
    printf("%d\n", my_str_is_uppercase(str));
    return (0);
}