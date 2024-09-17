#include <stdio.h>

int my_str_is_printable(char *str);

int
    main(void)
{
    char str[] = "HelloWorld";
    printf("%d\n", my_str_is_printable(str));
    return (0);
}