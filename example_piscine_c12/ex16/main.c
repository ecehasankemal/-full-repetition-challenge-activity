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

void print_list(t_list *list)
{
    while (list != NULL)
    {
        my_putnbr(*(int *)list->data);
        my_putstr(" -> ");
        list = list->next;
    }
    my_putstr("NULL\n");
}

void
    my_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)());

int main(void)
{
    t_list *list = NULL;
    t_list *new_elem;
    int values[] = {42, 23, 16, 15, 8, 4};
    int i;

    for (i = 5; i >= 0; i--)
    {
        new_elem = my_create_elem(&values[i]);
        new_elem->next = list;
        list = new_elem;
    }

    my_putstr("Sıralamadan önce:\n");
    print_list(list);

    my_sorted_list_insert(&list, &values[0], cmd);

    my_putstr("Sıralamadan sonra:\n");
    print_list(list);

    return 0;
}
