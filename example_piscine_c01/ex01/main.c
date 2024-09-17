#include <stdio.h>

void my_ultimate_my(int *********nbr);

int
    main(void)
{
    int nbr = 0;
    int *p1 = &nbr;
    int **p2 = &p1;
    int ***p3 = &p2;
    int ****p4 = &p3;
    int *****p5 = &p4;
    int ******p6 = &p5;
    int *******p7 = &p6;
    int ********p8 = &p7;
    int *********p9 = &p8;

    my_ultimate_my(p9);
    printf("%d\n", nbr);
    return (0);
}