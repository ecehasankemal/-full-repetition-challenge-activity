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

void
    my_list_clear(t_list **begin_list)
{
    t_list *current;
    t_list *next;

    current = *begin_list;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *begin_list = NULL;
}

t_list
    my_list_at(t_list *begin_list, unsigned int nbr)
{
    unsigned int i;

    if (nbr == 0) // bu kosula gerek yok cunku 0. eleman zaten begin_list. anlasılması için ekledim
        return (*begin_list);
    i = 0;
    while (i < nbr && begin_list != NULL)
    {
        begin_list = begin_list->next;
        i++;
    }
    return (*begin_list);
}

void
    my_list_reverse(t_list **begin_list)
{
    t_list *prev;
    t_list *current;
    t_list *next;

    prev = NULL;
    current = *begin_list;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *begin_list = prev;
}


unsigned int    my_write(int fd, const void *buf, unsigned int count);
void            my_putchar(char c);
void            my_putstr(char *str);


void
    f(void *data)
{
    char *str;

    str = (char *)data;
    if (str == NULL)
    {
        my_putstr("Fatal error\n");
        return ;
    }
    my_putstr(str);
    my_putchar('\n');
}

void
    my_list_foreach(t_list *begin_list, void (*f)(void *))
{
    while (begin_list != NULL)
    {
        f(begin_list->data);
        begin_list = begin_list->next;
    }
}

int
    cmd(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void
    my_list_foreach_if(t_list *begin_list, void (*f)(void *), void *data_ref, int (*cmp)())
{
    while (begin_list != NULL)
    {
        if (cmp(begin_list->data, data_ref) == 0)
            f(begin_list->data);
        begin_list = begin_list->next;
    }
}

t_list
    *my_list_find(t_list *begin_list, void *data_ref, int (*cmp)())
{
    while (begin_list != NULL)
    {
        if (cmp(begin_list->data, data_ref) == 0)
            return (begin_list);
        begin_list = begin_list->next;
    }
    return (NULL);
}

void
    free_fct(void *data)
{
    //free(data);
}


void
    my_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *))
{
    t_list *current;
    t_list *prev;
    t_list *next;

    if (!begin_list || !*begin_list)
        return;
    current = *begin_list;
    prev = NULL;
    while (current != NULL)
    {
        next = current->next;
        if (cmp(current->data, data_ref) == 0)
        {
            free_fct(current->data);
            free(current);
            if (prev == NULL)
                *begin_list = next;
            else
                prev->next = next;
        }
        else
            prev = current;
        current = next;
    }
}

void
    my_list_merge(t_list **begin_list1, t_list *begin_list2)
{
    t_list *last;
	t_list *start;
	start = *begin_list1;
    if (start == NULL)
    {
        *start = *begin_list2;
        return ;
    }
    while (start->next != NULL)
        start = (start)->next;
    last = start;
    last->next = begin_list2;
    
}

// merge sort algoritması kullanılacak.
// listeyi ikiye böl
// her iki listeyi de sırala
// iki listeyi birleştir
// listeyi sırala

int
    cmp(void *a, void *b)
{
    return (*(int *)a - *(int *)b);
}

void
    my_list_split(t_list *begin_list, t_list **a, t_list **b)
{
    t_list *double_speed;
    t_list *single_speed;

    if (begin_list == NULL || begin_list->next == NULL)
    {
        *a = begin_list;
        *b = NULL;
        return ;
    }
    single_speed = begin_list;
    double_speed = begin_list->next;
    while (double_speed != NULL)
    {
        double_speed = double_speed->next;
        if (double_speed != NULL)
        {
            single_speed = single_speed->next;
            double_speed = double_speed->next;
        }
    }
    *a = begin_list;
    *b = single_speed->next;
    single_speed->next = NULL;
}

t_list
    *my_list_merge_2(t_list *a, t_list *b, int (*cmp)())
{
    t_list *result;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (cmp(a->data, b->data) <= 0)
    {
        result = 0;
        result->next = my_list_merge_2(a->next, b, cmp);
    }
    else
    {
        result = b;
        result->next = my_list_merge_2(a, b->next, cmp);
    }
    return (result);
}

void
    my_list_sort(t_list **begin_list, int (*cmp)())
{
    t_list *a;
    t_list *b;
    t_list *head;

    head = *begin_list;

    if (head == NULL || head->next == NULL)
        return ;
    my_list_split(head, &a, &b);
    my_list_sort(&a, cmp);
    my_list_sort(&b, cmp);
    *begin_list = my_list_merge_2(a, b, cmp);
}


// merge sort kullanalım.



void
    my_list_reverse_fun(t_list *begin_list)
{
    t_list *save_begin_list;
    t_list *a;
    t_list *b;

    save_begin_list = begin_list;
    if (begin_list == NULL || begin_list->next == NULL)
        return ;
    my_list_split(begin_list, &a, &b);
    my_list_reverse_fun(a);
    my_list_reverse_fun(b);
    begin_list = my_list_merge_2(a, b, cmp);
}

void my_sorted_list_insert(t_list **begin_list,void *data, int (*cmp)())
{
	t_list	*list_ptr;
	t_list	*other_list_ptr;
	t_list	*swap;
	t_list	*new_node;

	list_ptr = (*begin_list);
	new_node = my_create_elem(data);
	new_node->next = (*begin_list);
	*begin_list = new_node;
	while(list_ptr != NULL)
	{
		other_list_ptr = list_ptr->next;
		while(other_list_ptr != NULL)
		{
			if((*cmp)(list_ptr->data, other_list_ptr->data) > 0)
			{
				swap = list_ptr->data;
				list_ptr->data = other_list_ptr->data;
				other_list_ptr->data = swap;
			}
			other_list_ptr = other_list_ptr->next;
		}
		list_ptr = list_ptr->next;
	}
}

void
    my_sorted_list_merge(t_list **begin_list1, t_list *begin_list2, int (*cmp)())
{
    t_list *last;
    t_list *start;
    start = *begin_list1;
    if (start == NULL)
    {
        *start = *begin_list2;
        return ;
    }
    while (start->next != NULL)
        start = (start)->next;
    last = start;
    last->next = begin_list2;
    my_list_sort(begin_list1, cmp);
}