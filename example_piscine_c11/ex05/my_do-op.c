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

void
     my_do_op(char op, int a, int b)
{
    if (op == '+')
        my_putnbr(a + b);
    else if (op == '-')
        my_putnbr(a - b);
    else if (op == '*')
        my_putnbr(a * b);
    else if (op == '/')
    {
        if (b == 0 || a == 0) 
            my_putstr("Stop : division by zero");
        else
            my_putnbr(a / b);
    }
    else if (op == '%')
    {
        if (b == 0 || a == 0)
            my_putstr("Stop : modulo by zero");
        else
            my_putnbr(a % b);
    }
    else
        my_putchar('0');
    my_putchar('\n');
}

int
     my_getnbr(char *str)
{
    int     nb;
    int     sign;

    nb = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    while (*str == '-' || *str == '+')
        if (*str++ == '-')
            sign *= -1;
    while (*str >= '0' && *str <= '9')
        nb = nb * 10 + *str++ - '0';
    return (nb * sign);
}

int
     main(int ac, char **av)
{
    if (ac == 4)
        my_do_op(av[2][0], my_getnbr(av[1]), my_getnbr(av[3]));
    return (0);
}

