#include <stdio.h>

char *my_strjoin(int size, char **strs, char *sep);

int main(void)
{
    char *strs[] = {"kemal", "kurt", "anlamak", NULL};
    char *sep = "; ";
    char *result = my_strjoin(3, strs, sep);
    printf("%s\n", result);
    return (0);
}