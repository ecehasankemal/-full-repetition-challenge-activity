#ifndef MY_HEXDUMP_H
# define MY_HEXDUMP_H

# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# define BUFFER_SIZE 16


void    my_hexdump(char *filename);
void    print_error(const char *message);
void    print_hex(unsigned char byte);
void    print_hexdump_line(char *buf, ssize_t bytes_read);

#endif