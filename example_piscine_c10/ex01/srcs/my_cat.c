#include "../inc/my_cat.h"

size_t
    my_strlen(char *str)
{
    size_t  i;

    i = 0;
    while (*str++)
        i++;
    return (i);
}

void
    my_cat(char *filename)
{
    int     fd;
    char    buf[30];
    ssize_t bytes_read;

    if (filename == NULL)
        fd = 0;
    else
    {
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
            write(2, "Cannot read file: ", 18);
            write(2, strerror(errno), my_strlen(strerror(errno)));
            // No such file or directory
            write(2, "\n", 1);
            return;
        }
    }

    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0)
        write(1, buf, bytes_read);

    if (bytes_read == -1)
    {
        write(2, "Read error: ", 12);
        write(2, strerror(errno), my_strlen(strerror(errno)));
        write(2, "\n", 1);
    }

    if (fd != 0)
        close(fd);
}
