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


// my_list_remove_if denenecek
void    my_list_foreach_if(t_list *begin_list, void (*f)(void *), void *data_ref, int (*cmp)());
t_list *my_list_find(t_list *begin_list, void *data_ref, int (*cmp)());
void    my_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));


int
    main(void)
{
    t_list *list;

    list = my_create_elem("Hello");
    my_list_push_front(&list, "World");
    my_list_push_front(&list, "Test");
    my_list_push_front(&list, "Remove me");
    my_list_push_front(&list, "Another Test");

    my_putstr("Before remove:\n");
    my_list_foreach(list, &f);
    my_putchar('\n');

    my_putstr("After remove:\n");
    my_list_remove_if(&list, "Remove me", &cmd, &free_fct);
    my_list_foreach(list, &f);
    my_putchar('\n');

    return (0);
}


