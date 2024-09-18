int
    my_recursive_power(int nb, int power)
{
    if (power < 0)
        return (0);
    else if (power == 0)
        return (1);
    return (nb * my_recursive_power(nb, power - 1));
}