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

t_list
    *my_list_last(t_list *begin_list)
{
    if (begin_list == NULL)
        return (NULL);
    while (begin_list->next != NULL)
        begin_list = begin_list->next;
    return (begin_list);
}

void
    my_list_push_back(t_list **begin_list, void *data)
{
    t_list *new_elem = my_create_elem(data);
    t_list *current;

    if (*begin_list == NULL)
    {
        *begin_list = new_elem;  // Liste boşsa, ilk elemanı ekle
    }
    else
    {
        current = *begin_list;
        while (current->next != NULL)  // Listenin sonuna git
        {
            current = current->next;
        }
        current->next = new_elem;  // Sonuna yeni elemanı ekle
    }
}

t_list
    *my_list_push_strs(int size, char **strs)
{
    t_list *list;
    int i;

    list = NULL;
    i = 0;
    while (i < size)
    {
        my_list_push_back(&list, strs[i]);
        i++;
    }
    return (list);
}