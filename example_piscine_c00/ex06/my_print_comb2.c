#include <unistd.h>

void
    my_print_comb2(void)
{
    char arr[4] = {'0', '0', '0', '0'};

    while (arr[0] <= '9') // arr[0] ilk sayıyı temsil eder
    {
        while (arr[1] <= '9') // arr[1] ikinci sayıyı temsil eder
        {
            arr[2] = arr[0];
            arr[3] = arr[1] + 1; // ilk sayıya göre ikinci sayıyı bir arttırıyoruz
            while (arr[2] <= '9') // arr[2] üçüncü sayıyı temsil eder
            {
                while (arr[3] <= '9') // arr[3] dördüncü sayıyı temsil eder
                {
                    write(1, arr, 2);
                    write(1, " ", 1);
                    write(1, arr + 2, 2);
                    if (!(arr[0] == '9' && arr[1] == '8' && arr[2] == '9' && arr[3] == '9'))
                    {
                        write(1, ", ", 2);
                    }
                    arr[3]++;
                }
                arr[3] = '0';
                arr[2]++;
            }
            arr[2] = '0';
            arr[1]++;
        }
        arr[1] = '0';
        arr[0]++;
    }
    
    write(1, "\n", 1);
}

// 00 00, 00 01, 00 02, 00 03, 00 04, 00 05, 00 06, 00 07, 00 08, 00 09
