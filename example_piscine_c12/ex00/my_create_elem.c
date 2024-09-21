#include "my_list.h"

/*
    typedef struct s_list
    {
        struct s_list *next;
        void *data;
    }               t_list;
*/

t_list  *my_create_elem(void *data)
{
    t_list *elem;

    elem = (t_list *)malloc(sizeof(t_list));
    if (elem == NULL)
        return (NULL);
    elem->data = data;
    elem->next = NULL;
    return (elem);
}