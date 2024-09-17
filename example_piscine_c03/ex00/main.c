#include <stdio.h>

int my_strcmp(char const *s1, char const *s2);

int
    main(void)
{
    char const *s1 = "Hello";
    char const *s2 = "Hello";
    printf("%d\n", my_strcmp(s1, s2));
    return (0);
}