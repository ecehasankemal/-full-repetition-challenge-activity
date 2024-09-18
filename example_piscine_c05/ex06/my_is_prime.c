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