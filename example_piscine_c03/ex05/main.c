#include <stdio.h>

unsigned int my_strlcat(char *dest, char const *src, unsigned int size);

int
    main(void)
{
    char dest[50] = "Hello";
    char const *src = " World!";
    printf("%u\n", my_strlcat(dest, src, 5));
    printf("%s\n", dest);
    return (0);
}