#ifndef FILE_H
#define FILE_H

typedef struct {
    char path[1000];
    char hash[65];
} FileInfo;

typedef struct {
    FileInfo *files;
    int size;
    int capacity;
} FileList;

void initFileList(FileList *list);
void addFile(FileList *list, char *path, char *hash);
void freeFileList(FileList *list);

#endif