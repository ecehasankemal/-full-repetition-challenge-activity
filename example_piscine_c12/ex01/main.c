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

t_list *my_create_elem(void *data);
void my_list_push_front(t_list **begin_list, void *data);

int
    main(void)
{
    t_list *elem;
    t_list *elem2;
    t_list **begin_list;

    begin_list = (t_list **)malloc(sizeof(t_list *));
    elem = my_create_elem("Hello, World!");
    elem2 = elem;
    if (elem == NULL)
        return (1);
    my_putstr((char *)elem->data);
    my_putchar('\n');
    my_list_push_front(begin_list, elem->data);
    my_putstr((char *)(begin_list[0])->data);
    my_putchar('\n');

    return (0);
}