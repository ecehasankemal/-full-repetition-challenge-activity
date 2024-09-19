#include "../inc/my_tail.h"

int
    my_atoi(char *str)
{
    int     result;
    int     sign;

    result = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + *str - '0';
        str++;
    }
    return (result * sign);
}

size_t
    my_strcmp(char const *s1, char const *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}

size_t
    my_strlen(char const *str)
{
    size_t  i;

    i = 0;
    while (*str++)
        i++;
    return (i);
}

void
    print_error(const char *message)
{
    write(2, message, my_strlen(message));
    write(2, strerror(errno), my_strlen(strerror(errno)));
    write(2, "\n", 1);
}

void
    my_tail(int byte_count, char *filename)
{
    int     fd;
    off_t   file_size;
    off_t   offset;
    ssize_t bytes_read;
    char    buf[BUFFER_SIZE];

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        print_error("Cannot read file: ");
        return;
    }

    file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1)
    {
        print_error("Failed to get file size: ");
        close(fd);
        return;
    }
    offset = (file_size > byte_count) ? file_size - byte_count : 0;
    if (lseek(fd, offset, SEEK_SET) == -1)
    {
        print_error("Failed to seek file: ");
        close(fd);
        return;
    }
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0)
    {
        ssize_t  bytes_to_write;

        bytes_to_write = bytes_read;
        if (offset + bytes_to_write > file_size)
            bytes_to_write = file_size - offset;
        write(1, buf, bytes_to_write);
        offset += bytes_to_write;
        if (offset >= file_size)
            break;
        
    }
    if (bytes_read == -1)
        print_error("Read error: ");
    close(fd);
}

// NOT: proje lseek kullanımına izin vermiyor. Bu yüzden bu fonksiyonu kullanamayız.
// Ben üşendiğim için bu fonksiyonu yazdım. Ama siz yazmayın.