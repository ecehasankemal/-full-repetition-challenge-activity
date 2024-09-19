#include "../inc/my_hexdump.h"

void
    print_error(const char *message)
{
    write(2, message, strlen(message));
    write(2, strerror(errno), strlen(strerror(errno)));
    write(2, "\n", 1);
}

void
    print_hex(unsigned char byte)
{
    const char *hex = "0123456789abcdef";
    write(1, &hex[byte / 16], 1);
    write(1, &hex[byte % 16], 1);
}

void
    print_hexdump_line(char *buf, ssize_t bytes_read)
{
    ssize_t         i;
    unsigned char   c;

    i = 0;
    while (i < bytes_read)
    {
        print_hex(buf[i]);
        if (i % 2 == 1)
            write(1, " ", 1);
        i++;
    }
    while (i < BUFFER_SIZE)
    {
        write(1, "  ", 2);
        if (i % 2 == 1)
            write(1, " ", 1);
        i++;
    }
    i = 0;
    write(1, "|", 1);
    while (i < bytes_read)
    {
        c = buf[i];
        if (c >= 32 && c <= 126)
            write(1, &c, 1);
        else
            write(1, ".", 1);
        i++;
    }
    write(1, "|\n", 2);
}

void
    my_hexdump(char *filename)
{
    int     fd;
    ssize_t bytes_read;
    char    buf[BUFFER_SIZE];
    off_t   offset;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        print_error("Cannot read file: ");
        return;
    }
    offset = 0;
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0)
    {
        print_hexdump_line(buf, bytes_read);
        offset += bytes_read;
    }
    if (bytes_read == -1)
        print_error("Read error: ");
    close(fd);
}