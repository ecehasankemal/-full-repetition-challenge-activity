#include <stdio.h>

int my_str_is_lowercase(char *str);

int
    main(void)
{
    char str[] = "hello";
    printf("%d\n", my_str_is_lowercase(str));
    return (0);
}