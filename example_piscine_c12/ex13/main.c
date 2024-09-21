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


// my_list_merge denenecek bu kesin denenecek

void
    my_list_merge(t_list **begin_list1, t_list *begin_list2);

int
    main(void)
{
    t_list **begin_list1;
    t_list *begin_list2;

    *begin_list1 = my_create_elem("1");
    my_list_push_back(begin_list1, "2");
    my_list_push_back(begin_list1, "3");
    my_list_push_back(begin_list1, "4");
    my_list_push_back(begin_list1, "5");
    my_list_push_back(begin_list1, "6");
    my_list_push_back(begin_list1, "7");
    my_list_push_back(begin_list1, "8");
    my_list_push_back(begin_list1, "9");
    my_list_push_back(begin_list1, "10");

    begin_list2 = my_create_elem("11");
    my_list_push_back(&begin_list2, "12");
    my_list_push_back(&begin_list2, "13");
    my_list_push_back(&begin_list2, "14");
    my_list_push_back(&begin_list2, "15");
    my_list_push_back(&begin_list2, "16");
    my_list_push_back(&begin_list2, "17");
    my_list_push_back(&begin_list2, "18");
    my_list_push_back(&begin_list2, "19");
    my_list_push_back(&begin_list2, "20");

    my_list_merge(begin_list1, begin_list2);

    my_list_foreach(*begin_list1, f);
    return (0);
}


/*
Chapter XVI
Egzersiz 13 : ft_list_merge
Exercise 13
ft_list_merge
Turn-in directory : ex13/
Files to turn in : ft_list_merge.c, ft_list.h
Allowed functions : None
• begin2 listesinin öğelerini, begin1 listesinin sonuna koyacak bir ft_list_merge
fonksiyonu oluşturun.
• Öğe oluşturmaya izin yoktur.
• Prototipi şu şekilde olmalıdır :
void ft_list_merge(t_list **begin_list1, t_list *begin_list2);
*/


