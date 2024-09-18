#include "my_abs.h"
#include <stdio.h>

int main() {
    int a = -3;
    int b = 5;
    int c = ABS(a);
    int d = ABS(b);

    printf("a = %d, b = %d\n", a, b);
    printf("c = %d, d = %d\n", c, d);
    return 0;
}