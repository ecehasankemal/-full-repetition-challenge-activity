int
    my_is_prime(int nb)
{
    int     i;

    i = 2;
    if (nb <= 1) return (0); // 0 ile 1 asal sayı değildir.
    while (i < nb)
    {
        if (nb % i == 0) return (0); // Eğer nb, i'ye bölünüyorsa asal değildir.
        i++;
    }
    return (1); // Eğer hiçbir sayıya bölünmüyorsa asal sayıdır.
}

int
    my_find_next_prime(int nb)
{
    int     i;

    i = nb;
    while (i < 2147483647) 
    {
        if (my_is_prime(i) == 1) // Burada bunu yapma sebebimiz my_is_prime fonksiyonunu kullanarak asal sayıları bulmamız.
            return (i);
        i++;
    }
    return (0);
}