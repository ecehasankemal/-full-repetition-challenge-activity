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
void    my_list_reverse(t_list **begin_list);
void    my_list_foreach(t_list *begin_list, void (*f)(void *));
void    f(void *data);
void    my_list_foreach_if(t_list *begin_list, void (*f)(void *), void *data_ref, int (*cmp)());
int     cmd(char *s1, char *s2);
void    free_fct(void *data);
void    my_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
void    my_list_merge(t_list **begin_list1, t_list *begin_list2);
void    my_list_sort(t_list **begin_list, int (*cmp)());
void    my_list_split(t_list *source, t_list **front_ref, t_list **back_ref);
t_list  *my_list_merge_2(t_list *a, t_list *b, int (*cmp)());


#endif