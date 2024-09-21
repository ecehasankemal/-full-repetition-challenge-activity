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

void my_list_push_back(t_list **begin_list, void *data);

int
    main(void)
{
    t_list *elem;
    t_list *ananınami;
    t_list **begin_list;
    int     index;
    char    *m_data[10] = {"kemal", "ali", "veli", "deli",
                           "mehmet", "ahmet", "hasan", "hüseyin", "mehmet", "ahmet"};

    index = 0;
    begin_list = (t_list **)malloc(sizeof(t_list *));
    *begin_list = NULL;
    elem = my_create_elem("Hello, World!");
    if (begin_list == NULL || elem == NULL)
        return (1);

    my_putstr((char *)elem->data);
    my_putchar('\n');

    while (index < 10)
    {
        my_list_push_back(begin_list, m_data[index]);
        // eğer burada my_list_push_front kullansa idik ilk kemali koyup
        // önüne aliyi koyacaktı bu yüzden en son eleman her daim kemal olacaktı.
        // bu yüzden biz de my_list_push_back kullandık ki en son eleman ahmet olsun.
        index++;
    }
    ananınami = my_list_last(begin_list[0]);
    my_putstr((char *)ananınami->data);
    my_putchar('\n');
    return (0);
}