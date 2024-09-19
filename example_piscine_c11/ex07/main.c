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

int
    my_putstr(char *str)
{
    while (*str)
        my_putchar(*str++);
}

void    my_advanced_sort_string_tab(char **tab, int(*cmp)(char *, char *));
int     cmp(char *a, char *b);

int
    main(void)
{
    char    *tab[7] = {"is fun ", "World ", "Hello", "42 ", "C ", "Zebra ", (char *)0};
    int    i;
    
    my_advanced_sort_string_tab(tab, &cmp);
    i = 0;
    while (tab[i])
    {
        my_putstr(tab[i]);
        my_putchar('\n');
        i++;
    }
    return (0);
}