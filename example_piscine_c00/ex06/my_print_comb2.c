#include <unistd.h>

void
    my_print_comb2(void)
{
    // 00 00, 00 01, 00 02, 00 03, 00 04, 00 05, 00 06, 00 07, 00 08, 00 09

    char a;
    char b;
    char c;
    char d;

    a = '0';
    b = '0';
    c = '0';
    d = '0';

    while (a <= '9')
    {
        while (b <= '9')
        {
            c = a;
            d = b + 1; // ilk sayıya göre ikinci sayıyı bir arttırıyoruz
            while (c <= '9')
            {
                while(d <= '9')
                {
                    write(1, &a, 1);
                    write(1, &b, 1);
                    write(1, " ", 1);
                    write(1, &c, 1);
                    write(1, &d, 1);
                    if (!(a == '9' && b == '8' && c == '9' && d == '9'))
                    {
                        write(1, ", ", 2);
                    }
                    d++;
                }
                d = '0';
                c++;
            }
            c = '0';
            b++;
        }
        b = '0';
        a++;
    }
    write(1, "\n", 1);
}