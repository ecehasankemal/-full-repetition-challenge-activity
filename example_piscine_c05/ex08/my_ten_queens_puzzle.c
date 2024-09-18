#include <unistd.h>

void
    my_putchar(char c)
{
    write(1, &c, 1);
}

void
    my_putnbr(int nb)
{
    long n;

    n = nb;
    if (n < 0)
    {
        my_putchar('-');
        n = -n;
    }
    if (n >= 10)
    {
        my_putnbr(n / 10);
        my_putnbr(n % 10);
    }
    else
        my_putchar(n + '0');
}

int
    my_ten_queens_puzzle_recursive(int arr[10], int index, int count)
{
    int     i;
    int     j;
    int     h;

    if (index == 10)
    {
        h = 0;
        while (h < 10)
        {
            my_putnbr(arr[h]);
            h++;
        }
        my_putchar('\n');
        return (count + 1);
    }
    i = 0;
    while (i < 10)
    {
        j = 0;
        while (j < index)
        {
            if (arr[j] == i || arr[j] == i + index - j || arr[j] == i - index + j)
                break;
            j++;
        }
        if (j == index)
        {
            arr[index] = i;
            count = my_ten_queens_puzzle_recursive(arr, index + 1, count);
        }
        i++;
    }
    return (count);
}

int
    my_ten_queens_puzzle(void)
{
    // recursive fonskiyon kullanmam gerekiyor
    // 10 tane vezirin birbirini yememesi gerekiyor
    // vezirlerin birbirini yemediği durumları bulmam gerekiyor
    // 10 tane vezirin birbirini yemediği durumları bulmam gerekiyor

    int arr[10];
    int     count;
    int     index;

    index = 0;
    count = 0;
    while (index < 10) { arr[index] = -1; index++; }
    count = my_ten_queens_puzzle_recursive(arr, 0, count);
    return (count);    
}

/*
$>./a.out | cat -e
0257948136$
0258693147$
...
4605713829$
4609582731$
...
9742051863$
$>
*/
