#include <stdlib.h>
#include "my_strs_to_tab.h"

struct s_stock_str *my_strs_to_tab(int ac, char **av)
{
    t_stock_str *stock;
    int i = 0;

    stock = malloc(sizeof(t_stock_str) * (ac + 1));
    if (stock == NULL)
        return (NULL);
    while (i < ac)
    {
        stock[i].size = 0;
        while (av[i][stock[i].size] != '\0')
            stock[i].size++;
        stock[i].str = av[i];
        stock[i].copy = malloc(sizeof(char) * (stock[i].size + 1));
        if (stock[i].copy == NULL)
            return (NULL);
        stock[i].copy[stock[i].size] = '\0';
        int thrash = stock[i].size;
        while (thrash >= 0)
        {
            stock[i].copy[thrash] = av[i][thrash];
            thrash--;
        }
        i++;
    }
    stock[i].size = 0;
    stock[i].str = 0;
    stock[i].copy = 0;
    return (stock);
}