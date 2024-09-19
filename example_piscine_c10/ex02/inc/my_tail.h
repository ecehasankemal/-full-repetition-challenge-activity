#ifndef MY_TAIL_H
# define MY_TAIL_H

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

void    print_error(const char *message);
void    my_tail(int byte_count, char *filename);
size_t  my_strlen(char const *str);
size_t  my_strcmp(char const *s1, char const *s2);
int     my_atoi(char *str);

#endif