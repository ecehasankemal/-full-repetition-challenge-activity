#include <stdio.h>

int my_str_is_alpha(char *str);

int
    main(void)
{
    char str[] = "HelloWorld";
    printf("%d\n", my_str_is_alpha(str));
    return (0);
}