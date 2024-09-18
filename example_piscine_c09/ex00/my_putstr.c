void my_putchar(char c);

void
    my_putstr(char *str)
{
    while (*str)
        my_putchar(*str);
}