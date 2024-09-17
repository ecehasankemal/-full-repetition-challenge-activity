#include <unistd.h>

void    my_strncpy(char *dest, char *src, unsigned int n);

int my_strlen(const char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int
    main(void)
{
    char src[] = "Hello, World!";
    char dest[14];
    my_strncpy(dest, src, 5);
    write(1, dest, my_strlen(dest));
    write(1, "\n", 1);
    return (0);
}