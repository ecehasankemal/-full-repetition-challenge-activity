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

int my_count_if(char **tab, int length, int(*f)(char*));

int my_str_is_not_empty(char *str)
{
    return (str && *str != '\0');  // Eğer string boş değilse 1 döndür
}

int
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

int
    main(void)
{
    char    *tab[6] = {"Hello ", "World ", "42 ", "C ", "is fun ", (char *)0};
    int    res;

    res = my_count_if(tab, 6, &my_str_is_not_empty);
    my_putstr(my_count_if(tab, 6, &my_str_is_not_empty) ? "True\n" : "False\n");
    my_putstr("res: ");
    my_putnbr(res);
    my_putchar('\n');
    return (0);
}