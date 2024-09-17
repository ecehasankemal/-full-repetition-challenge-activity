void
    my_ultimate_div_mod(int *a, int *b)
{
    int temp = *a;
    *a = *a / *b;
    *b = temp % *b;
}