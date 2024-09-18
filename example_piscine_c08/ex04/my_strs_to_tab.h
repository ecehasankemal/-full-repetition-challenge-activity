#ifndef MY_STRS_TO_TAB_H
# define MY_STRS_TO_TAB_H

typedef struct s_stock_str
{
int size;
char *str;
char *copy;
}               t_stock_str;

struct s_stock_str *my_strs_to_tab(int ac, char **av);
#endif