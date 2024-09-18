#include <stdio.h>
#include "my_strs_to_tab.h"



int main(int ac, char **av)
{
    t_stock_str *stock;
    int i = 0;

    stock = my_strs_to_tab(ac, av);
    while (stock[i].str != 0)
    {
        printf("size = %d, str = %s, copy = %s\n", stock[i].size, stock[i].str, stock[i].copy);
        i++;
    }
    return (0);
}