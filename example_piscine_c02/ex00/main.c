#include <unistd.h>

char    *my_strcpy(char *dest, char *src);

int
    main(void)
{
    char src[] = "Hello, World!";
    char dest[14];
    my_strcpy(dest, src);
    write(1, dest, 14);
    write(1, "\n", 1);
    return (0);
}