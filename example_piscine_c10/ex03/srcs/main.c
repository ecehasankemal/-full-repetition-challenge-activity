#include "../inc/my_hexdump.h"

int
    main(int argc, char **argv)
{
    if (argc != 2)
    {
        print_error("Usage: my_hexdump filename");
        return (1);
    }
    my_hexdump(argv[1]);
    return (0);
}