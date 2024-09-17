#include <stdio.h>

char *my_strupcase(char *str);

int
    main(void)
{
    char str[] = "HelloWorld";
    printf("%s\n", str);
    printf("%s\n", my_strupcase(str));
    return (0);
}