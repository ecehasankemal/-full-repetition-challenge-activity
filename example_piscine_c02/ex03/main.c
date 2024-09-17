#include <stdio.h>

int my_str_is_numeric(char *str);

int
    main(void)
{
    char str[] = "1234567890";
    printf("%d\n", my_str_is_numeric(str));
    return (0);
}