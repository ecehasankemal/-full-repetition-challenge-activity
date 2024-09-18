#include <stdlib.h>
#include <stdio.h>

int
    my_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int
    check_base(char *base)
{
    int i;
    int j;

    i = 0;
    while (base[i])
    {
        if (base[i] == '+' || base[i] == '-' || base[i] == ' ' || (base[i] >= 9 && base[i] <= 13))
            return (0);
        j = i + 1;
        while (base[j])
        {
            if (base[i] == base[j])
                return (0);
            j++;
        }
        i++;
    }
    if (i < 2)
        return (0);
    return (1);
}

int
    my_char_to_int(char c, char *base)
{
    int i = 0;
    while (base[i])
    {
        if (base[i] == c)
            return i;
        i++;
    }
    return -1;
}

int my_atoi_base(char *str, char *base, int *is_neg)
{
    int num = 0;
    int base_len = my_strlen(base);
    
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    while (*str == '-' || *str == '+')
    {
        if (*str == '-')
            *is_neg = !(*is_neg);
        str++;
    }
    while (*str && my_char_to_int(*str, base) != -1)
    {
        num = num * base_len + my_char_to_int(*str, base);
        str++;
    }
    return (*is_neg ? -num : num);
}

char *my_itoa_base(int nbr, char *base)
{
    char buffer[64];
    int base_len;
    int i;
    int swap_index;
    int is_neg;
    char *result;

    swap_index = 0;
    i = 0;
    is_neg = 0;
    base_len = my_strlen(base);
    if (nbr < 0)
    {
        is_neg = 1;
        nbr = -nbr;
    }
    if (nbr == 0)
    {
        buffer[i++] = base[0];
    }
    else
    {
        while (nbr > 0)
        {
            buffer[i++] = base[nbr % base_len];
            nbr /= base_len;
        }
    }
    if (is_neg)
        buffer[i++] = '-';
    
    buffer[i] = '\0';
    // benim maindeki örneğimde normalde 24 oluyor buraya kadar biz bunu 42 yapmamız gerekiyor
    while (swap_index < i / 2)
    {
        char temp = buffer[swap_index];
        buffer[swap_index] = buffer[i - swap_index - 1];
        buffer[i - swap_index - 1] = temp;
        swap_index++;
    }
    
    result = (char *)malloc(sizeof(char) * (i + 1));
    if (result == NULL)
        return (NULL);
    swap_index = 0;
    while (swap_index < i)
    {
        result[swap_index] = buffer[swap_index];
        swap_index++;
    }
    result[i] = '\0';
    
    return result;
}

char
    *my_convert_base(char *nbr, char *base_from, char *base_to)
{
    int num;
    int is_neg = 0;
    char *result;
    
    if (!check_base(base_from) || !check_base(base_to))
        return (NULL);
    
    num = my_atoi_base(nbr, base_from, &is_neg);
    result = my_itoa_base(num, base_to);
    
    return (result);
}