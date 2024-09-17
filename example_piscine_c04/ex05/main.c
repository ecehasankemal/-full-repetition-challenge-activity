#include <stdio.h>

int my_atoi_base(char *str, char *base);

int
    main(void)
{
    char str[] = "67543585438";
    char base[] = "0123456789";

    printf("string: %s, hex result: %d ", str ,my_atoi_base(str, base));
    return (0);
}