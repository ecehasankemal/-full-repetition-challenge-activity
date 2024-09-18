#include <unistd.h>

int
    my_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int
    main(int argc, char **argv)
{
    write(1, argv[0], my_strlen(argv[0]));
    write(1, "\n", 1);
    return (0);
}