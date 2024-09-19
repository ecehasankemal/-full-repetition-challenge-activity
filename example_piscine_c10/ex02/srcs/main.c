#include "../inc/my_tail.h"

int
    main(int argc, char **argv)
{
    int byte_count;
    int iterator;

    iterator = 3;
    if (argc < 3 || my_strcmp(argv[1], "-c") != 0)
    {
        write(2, "Usage: ft_tail -c N file...\n", 29);
        return (1);
    }
    else if (argc == 3)
    {
        write(2, "Usage: ft_tail -c N file...\n", 29);
        return (1);
    }
    byte_count = my_atoi(argv[2]);
    if (byte_count <= 0) {
        write(2, "Invalid byte count\n", 20);
        return (1);
    }
    while (iterator < argc)
    {
        my_tail(byte_count, argv[iterator]);
        iterator++;
    }
    write(1, "\n", 1);
    return (0);
}