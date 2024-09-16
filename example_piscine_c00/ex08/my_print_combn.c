#include <unistd.h>

void
    my_putchar(char c)
{
    write(1, &c, 1);
}

void
    print_comb_recursive(int *arr, int index, int n, int start)
{
    int i;
    if (index == n)
    {
        i = 0;
        while (i < n)
        {
            my_putchar(arr[i] + '0');
            i++;
        }
        if (arr[0] < 10 - n)
        {
            my_putchar(',');
            my_putchar(' ');
        }
        return;
    }
    i = start;
    while (i < 10)
    {
        arr[index] = i;
        print_comb_recursive(arr, index + 1, n, i + 1);
        i++;
    }
}


void
    my_print_combn(int n)
{
    int arr[10];
    if (n > 0 && n < 10)
        print_comb_recursive(arr, 0, n, 0);
    my_putchar('\n');
}