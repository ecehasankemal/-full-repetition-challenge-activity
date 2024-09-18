#include <unistd.h>
#include <stdlib.h>
#include "my_show_tab.h"

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

char *my_itoa(int num)
{
    char *str;
    int temp_num = num;
    int len = 0;

    if (num == 0)
        return ("0");

    while (temp_num > 0)
    {
        temp_num /= 10;
        len++;
    }

    str = malloc(sizeof(char) * (len + 1));
    if (str == NULL)
        return (NULL);

    str[len] = '\0'; 

    while (len > 0)
    {
        str[len - 1] = (num % 10) + '0';
        num /= 10;
        len--;
    }

    return str;
}

void my_show_tab(struct s_stock_str *par)
{
    int i = 0;
    while (par[i].str != 0)
    {
        write(1, par[i].str, par[i].size);
        write(1, "\n", 1);

        write(1, par[i].copy, par[i].size);
        write(1, "\n", 1);


        char *size_str = my_itoa(par[i].size);
        write(1, size_str, sizeof(size_str)); 
        write(1, "\n", 1);
        i++;
    }   
}
