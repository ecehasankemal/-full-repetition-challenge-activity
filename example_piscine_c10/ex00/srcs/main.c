#include "../inc/my_display_file.h"

int
    main(int argc, char **argv)
{
    if (argc < 2)
        write(2, "File name missing.\n", 19);
    else if (argc > 2)
        write(2, "Too many arguments.\n", 20);
    else
        my_display_file(argv[1]);
    return (0);
}
