#ifndef FILE_MAPPER_H
#define FILE_MAPPER_H

#include <stddef.h>

struct file
{
    int fd;
    size_t size;
    char *name;
    void *content;
};

struct file *file_mapper(const char *filename);
void file_unmapper(struct file **f);

#endif /* !FILE_MAPPER_H */
