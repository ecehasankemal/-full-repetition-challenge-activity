#include <unistd.h>

int
    my_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void
    my_putstr(char *str)
{
    write(1, str, my_strlen(str));
}

int
    main(int argc, char **argv)
{
    int count;

    count = argc;
    while (--count > 0)
    {
        my_putstr(argv[count]);
        write(1, "\n", 1);
    }
    return (0);
}