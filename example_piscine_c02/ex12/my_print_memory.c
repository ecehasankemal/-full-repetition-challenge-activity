#include <unistd.h>

void
    my_putchar(char c)
{
    write(1, &c, 1);
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
    print_adress(unsigned long addr)
{
    char    *hex = "0123456789abcdef";
    char    str[16];
    int     i;

    i = 15;
    while (i >= 0)
    {
        str[i] = hex[addr % 16];
        addr /= 16;
        i--;
    }
    str[16] = '\0';
    my_putstr(str);
    my_putstr(": ");
}

void
    *my_print_memory(void *addr, unsigned int size)
{
    unsigned int i;
    unsigned int j;
    unsigned char *ptr;
    char *hex;

    hex = "0123456789abcdef";
    ptr = (unsigned char *)addr;
    i = 0;
    while (i < size)
    {
        // Bellek adresini yazdırma işlemi:
        print_adress((unsigned long )ptr + i);
        // ilk olarak hexadecimale olarak yazdırıyoruz
         j = 0;
         while (j < 16 && i + j < size)
         {
            // iki basamaklı hex değeri yazdırmak için
            if (ptr[i + j] < 16)
                write(1, "0", 1); // eğer tek basamaklı ise başa 0 ekliyoruz
            my_putchar(hex[ptr[i + j] / 16]); // yüksek basamak
            my_putchar(hex[ptr[i + j] % 16]); // düşük basamak
            if (j % 2 == 1)
                my_putchar(' '); // her iki hex çiftten sonra boşluk ekliyoruz
            j++;
         }
         // eğer satır tam dolmadı ise boşluk ekliyoruz
        while (j < 16)
        {
            write(1, "  ", 2);
            if (j % 2 == 1)
                my_putchar(' '); // her iki boşluktan sonra bir boşluk ekliyoruz
            j++;
        }
        // ascii değerlerini yazdırıyoruz
        j = 0;
        while (j < 16 && i + j < size)
        {
            if (ptr[i + j] >= 32 && ptr[i + j] < 127)
                my_putchar(ptr[i + j]);
            else
                my_putchar('.'); // eğer ascii değeri yazdırılamıyorsa nokta yazdırıyoruz
            j++;
        }
        my_putchar('\n');
        i += 16;         
    }
    return (addr);
}

// 4004a4a7cf550000@Jz�U: 426f 6e6a 6f75 7220 6c65 7320 616d 696e Bonjour les amin
