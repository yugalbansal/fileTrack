#include "file.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int createFt(char *path)
{
    char createPath[1000];
    snprintf(createPath, sizeof(createPath), "%s/.ft", path);
    return mkdir(createPath, 0755);
}

int saveIndex(int fd, FileInfo *file)
{
    char buffer[1100];
    int n = snprintf(buffer, sizeof(buffer),
                     "%s %s\n",
                     file->path,
                     file->hash);

    return write(fd, buffer, n);
}