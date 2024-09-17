#include <stdio.h>

char *my_strncat(char *dest, char const *src, unsigned int nb);

int
    main(void)
{
    char dest[50] = "Hello";
    char const *src = " World!";
    printf("%s\n", my_strncat(dest, src, 5)); // çıktı: Hello Worl olması gerekir.
    return (0);
}