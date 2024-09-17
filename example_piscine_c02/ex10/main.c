#include <stdio.h>

int my_strlcpy(char *dest, char *src, int size);

int
    main(void)
{
    char dest[6];
    char src[] = "HelloWorld";
    printf("%d\n", my_strlcpy(dest, src, 5));
    printf("%s\n", dest);
    return (0);
}