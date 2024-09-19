#include "../inc/my_cat.h"

int
    main(int argc, char **argv)
{
    int count;

    if (argc < 2)
        my_cat(NULL);
    else
    {
        count = 1;
        while (count < argc)
        {
            my_cat(argv[count]);
            count++;
        }
    }
    return (0);
}
