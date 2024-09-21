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


// Bağlı liste düğümü oluşturma fonksiyonu

void print_list(t_list *list)
{
    while (list != NULL)
    {
        my_putnbr(*(int *)list->data);
        my_putstr(" -> ");
        //printf("%d -> ", *(int *)list->data);
        list = list->next;
    }
    my_putstr("NULL\n");
    //printf("NULL\n");
}

// Ana fonksiyon
int main(void)
{
    t_list *list = NULL;
    t_list *new_elem;
    int values[] = {42, 23, 16, 15, 8, 4};
    int i;

    // Bağlı listeye elemanları ekleme
    for (i = 5; i >= 0; i--)
    {
        new_elem = my_create_elem(&values[i]);
        new_elem->next = list;
        list = new_elem;
    }

    // Sıralamadan önce listeyi yazdır
    my_putstr("Sıralamadan önce:\n");
    //printf("Sıralamadan önce:\n");
    print_list(list);

    // Listeyi sıralama
    my_list_sort(&list, cmd);

    // Sıralamadan sonra listeyi yazdır
    my_putstr("Sıralamadan sonra:\n");
    //printf("Sıralamadan sonra:\n");
    print_list(list);

    return 0;
}
