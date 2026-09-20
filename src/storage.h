#ifndef STORAGE_H
#define STORAGE_H
#include "file.h"

int createFt(char *path);
int saveIndex(int fd, FileInfo *file);

#endif