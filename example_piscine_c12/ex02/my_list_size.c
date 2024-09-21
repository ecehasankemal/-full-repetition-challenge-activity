#include "my_list.h"

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

void
    my_list_push_front(t_list **begin_list, void *data)
{
    t_list *elem;

    elem = my_create_elem(data);
    if (elem == NULL)
        return ;
    elem->next = *begin_list;
    *begin_list = elem;
}

int
    my_list_size(t_list *begin_list)
{
    int     count;

    count = 0;
    while (begin_list != NULL)
    {
        count++;
        begin_list = begin_list->next;
    }
    return (count);
}