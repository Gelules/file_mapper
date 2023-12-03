#include "file_mapper.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

struct file *file_mapper(const char *filename)
{
    struct stat s = { 0 };
    struct file *new = malloc(sizeof (struct file));
    if (new == NULL)
    {
        perror("Cannot malloc a struct file");
        goto error_malloc;
    }

    if ((new->name = malloc(strlen(filename) + 1)) == NULL)
    {
        perror("Cannot malloc a string of strlen(filename)");
        goto error_name;
    }
    new->name = strcpy(new->name, filename);

    if ((new->fd = open(new->name, O_RDONLY)) == -1)
    {
        perror("Cannot open(filename) in read-only");
        goto error_open;
    }

    if ((stat(new->name, &s)) == -1)
    {
        perror("Cannot stat(filename)");
        goto error_stat;
    }
    new->size = s.st_size;

    if ((new->content = mmap(NULL, new->size, PROT_READ, MAP_PRIVATE, new->fd, 0)) == MAP_FAILED)
    {
        perror("Cannot mmap for the file size");
        goto error_mmap;
    }

    return new;

error_mmap:
error_stat:
    close(new->fd);
error_open:
    free(new->name);
error_name:
    free(new);
error_malloc:
    return NULL;
}

void file_unmapper(struct file **f)
{
    free((*f)->name);
    close((*f)->fd);
    munmap((*f)->content, (*f)->size);
    free(*f);
    *f = NULL;
}
