#include <stdio.h>

int my_strncmp(char const *s1, char const *s2, int n);

int
    main(void)
{
    char const *s1 = "Hello";
    char const *s2 = "Hello";
    printf("%d\n", my_strncmp(s1, s2, 5));
    return (0);
}