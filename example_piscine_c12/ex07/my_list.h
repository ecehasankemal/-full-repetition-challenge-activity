#ifndef MY_LIST_H
# define MY_LIST_H

# include <stdlib.h>

typedef struct s_list
{
struct s_list *next;
void *data;
}               t_list;

t_list *my_create_elem(void *data);
void    my_list_push_front(t_list **begin_list, void *data);
int     my_list_size(t_list *begin_list);
t_list *my_list_last(t_list *begin_list);
void    my_list_push_back(t_list **begin_list, void *data);
t_list  *my_list_push_strs(int size, char **strs);
void    my_list_clear(t_list **begin_list) ;
t_list  my_list_at(t_list *begin_list, unsigned int nbr);

#endif