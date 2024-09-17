void my_putstr_non_printable(char *str);
void my_putchar(char c);

int main(void)
{
    char *str;

    str = "Coucou\ntu vas bien ?";
    my_putstr_non_printable(str);
    my_putchar('\n');
    return (0);
}