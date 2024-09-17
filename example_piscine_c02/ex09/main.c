#include <stdio.h>

char *my_strcapitalize(char *str);

int
    main(void)
{
    char str[] = "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un";
    printf("%s\n", str);
    printf("%s\n", my_strcapitalize(str));
    return (0);
}