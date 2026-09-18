#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "scanner.h"
#include "file.h"

int main(int argc, char *argv[]){
    // first task - argument check
    if(argc < 3 || strcmp(argv[1], "init") != 0){
        printf("Error: Usage: ./merkletree init <directory>\n");
        return 1;
    }
    
    char path[1000];
    strcpy(path, argv[2]);
   
    // now read dir 
    FileList list;
    initFileList(&list);
    ReadDirectory(path, &list);
    // print file names from saved list 
    for(int i = 0; i < list.size; i++) {
        printf("%s  :   %s\n", list.files[i].path, list.files[i].hash);
    }

    freeFileList(&list);
    return 0;
}

