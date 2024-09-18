#include <stdio.h>

char    *my_strdup(char *src);

int
    main(void)
{
    char *str = "Hello, World!";
    char *copy = my_strdup(str);
    printf("Original: %s\n", str);
    printf("Copy:     %s\n", copy);
    return (0);
}