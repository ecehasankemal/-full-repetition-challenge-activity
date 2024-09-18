#include <unistd.h>

int
    my_strlen(char const *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void
    my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}

int
    my_strcmp(char const *s1, char const *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

void
    my_sort_params(int argc, char **argv)
{
    char    *temp;
    int     index;

    index = 0;
    while (++index < argc - 1)
    {
        if (my_strcmp(argv[index], argv[index + 1]) > 0)
        {
            temp = argv[index];
            argv[index] = argv[index + 1];
            argv[index + 1] = temp;
            index = 0;
        }
    }
}

int
    main(int argc, char **argv)
{
    int count;

    count = 0;
    my_sort_params(argc, argv);
    while (++count < argc)
    {
        my_putstr(argv[count]);
        write(1, "\n", 1);
    }
    return (0);
}