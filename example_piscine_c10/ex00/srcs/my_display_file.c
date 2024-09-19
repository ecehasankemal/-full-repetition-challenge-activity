#include "../inc/my_display_file.h"

void
    my_display_file(char *filename)
{
    int     fd;
    char    buf[1];

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        write(2, "Cannot read file.\n", 18);
        return;
    }
    while (read(fd, buf, 1) > 0)
        write(1, buf, 1);
    close(fd);
}