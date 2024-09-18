#include "my_show_tab.h"

int
main(int ac, char **av)
{
    t_stock_str *stock;
    int i = 0;

    stock = my_strs_to_tab(ac, av);
    my_show_tab(stock);
    return (0);
}


