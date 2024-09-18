int
    my_fibonacci(int index)
{
    if (index < 0)
        return (-1);
    else if (index == 0)
        return (0);
    else if (index == 1)
        return (1);
    return (my_fibonacci(index -1) + my_fibonacci(index - 2));
}