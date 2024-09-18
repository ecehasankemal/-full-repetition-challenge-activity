#include <stdio.h>

char *my_convert_base(char *nbr, char *base_from, char *base_to);

int
    main(void)
{
    char *nbr = "101010";
    char *base_from = "01";
    char *base_to = "0123456789";
    char *result = my_convert_base(nbr, base_from, base_to);
    printf("%s\n", result);
    return (0);
}