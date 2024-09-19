#ifndef MY_CAT_H
# define MY_CAT_H

# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>

# include <errno.h>
# include <string.h>
# include <libgen.h>

void    my_cat(char *filename);
size_t  my_strlen(char *str);

#endif
