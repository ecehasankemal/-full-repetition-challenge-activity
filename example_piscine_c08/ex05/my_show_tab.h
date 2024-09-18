#ifndef MY_SHOW_TAB_H
# define MY_SHOW_TAB_H

typedef struct s_stock_str
{
int size;
char *str;
char *copy;
}               t_stock_str;

void my_show_tab(struct s_stock_str *par);
struct s_stock_str *my_strs_to_tab(int ac, char **av);

#endif