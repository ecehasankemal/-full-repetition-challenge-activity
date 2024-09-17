#include <stdio.h>

void my_my(int *nbr);

int
    main(void)
{
    int nbr = 0;

    my_my(&nbr);
    printf("%d\n", nbr);
    return (0);
}