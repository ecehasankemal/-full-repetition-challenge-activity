#include <stdio.h>
#include <string.h>

int my_strlen(const char *str);

int
    main(void)
{
    char str[] = "Hello, World!";

    printf("%d\n", my_strlen(str));
    printf("%d\n", strlen(str));

    return (0);
}