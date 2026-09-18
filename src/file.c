#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

void initFileList(FileList *list){
    list->files = NULL;
    list->size = 0;
    list->capacity = 0;
}

void addFile(FileList *list, char *path, char *hash){
    if(list->size == list->capacity){
        if(list->capacity == 0){
            list->capacity = 10;
        }
        else{
            list->capacity *=2;
        }
        list->files = realloc(list->files, list->capacity * sizeof(FileInfo));
    }

    strcpy(list->files[list->size].path, path);
    strcpy(list->files[list->size].hash, hash);
    list->size++;
}

void freeFileList(FileList *list) {
    free(list->files);
}