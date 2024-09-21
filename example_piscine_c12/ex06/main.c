#include "my_list.h"

unsigned int
    my_write(int fd, const void *buf, unsigned int count)
{
    unsigned long long ret;

    __asm__ volatile
    (
        // sys_write sistem çağrısının numarası (rax = 1)
        "mov $1, %%rax;"        // 1'i (sys_write) rax'a taşı

        // Dosya tanımlayıcısı (rdi = fd)
        "mov %1, %%rdi;"        // fd'yi rdi'ye taşı

        // Bellek adresi (rsi = buf)
        "mov %2, %%rsi;"        // buf'u rsi'ye taşı

        // Sayı (rdx = count)
        "mov %3, %%rdx;"        // count'u rdx'e taşı

        // Sistem çağrısını gerçekleştir
        "syscall;"

        // Sonucu kaydet
        "mov %%rax, %0;"
        : "=r" (ret)            // Çıkış operandı
        : "r" ((unsigned long long)fd), "r" ((unsigned long long)buf), "r" ((unsigned long long)count) // Giriş operandları
        : "%rax", "%rdi", "%rsi", "%rdx"   // Kullanılan registerler (bozulabilecek olanlar)
    );

    return (unsigned int)ret;
}

void
    my_putchar(char c)
{
    my_write(1, &c, 1);
}

void
    my_putstr(char *str)
{
    while (*str)
    {
        my_putchar(*str);
        str++;
    }
}

void
    my_putnbr(int n)
{
    long    nb;

    nb = n;
    if (nb < 0)
    {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
    {
        my_putnbr(nb / 10);
        my_putnbr(nb % 10);
    }
    else
        my_putchar(nb + '0');
}


// my_list_clear denenecek

int
    main(void)
{
    t_list *list;
    char *strs[] = {"Hello", "World", "!", NULL};

    list = my_list_push_strs(3, strs);
    if (list == NULL)
        return (1);
    
    my_putstr("List: size: ");
    my_putnbr(my_list_size(list));
    my_putchar('\n');

    my_putstr("First element: ");
    my_putstr((char *)list->data);
    my_putchar('\n');

    my_putstr("Second element: ");
    my_putstr((char *)list->next->data);
    my_putchar('\n');

    my_putstr("Last element: ");
    my_putstr((char *)my_list_last(list)->data);
    my_putchar('\n');

    my_list_clear(&list);
    my_putstr("List: size: ");
    my_putnbr(my_list_size(list));
    my_putchar('\n');

    return (0);
}