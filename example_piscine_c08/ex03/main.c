#include "my_point.h"
#include <stdio.h>

void set_point(my_point *point)
{
point->x = 42;
point->y = 21;
}
int main(void)
{
my_point point;
set_point(&point);
printf("x = %d, y = %d\n", point.x, point.y);
return (0);
}