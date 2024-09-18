int
    my_recursive_factorial(int nb)
{
    if (nb < 0)
        return (0);
    if (nb == 0)
        return (1);
    return (nb * my_recursive_factorial(nb - 1));
}