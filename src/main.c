#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "scanner.h"
#include "file.h"
#include "storage.h"

int main(int argc, char *argv[])
{
    // first task - argument check
    if (argc < 3 != 0)
    {
        printf("Error: Usage: ./merkletree init <directory>\n");
        return 1;
    }
    if (strcmp(argv[1], "init") == 0)
    {
        char path[1000];
        strcpy(path, argv[2]);
        // now read dir
        FileList list;
        initFileList(&list);
        ReadDirectory(path, &list);
        createFt(path);
        // print file names from saved list
        char indexPath[1100];
        snprintf(indexPath, sizeof(indexPath), "%s/.ft/index", path);
        int fd = open(indexPath, O_RDWR | O_TRUNC | O_CREAT , 0644);
        for (int i = 0; i < list.size; i++)
        {
            saveIndex(fd, &list.files[i]);
            printf("%s  :   %s\n", list.files[i].path, list.files[i].hash);
        }
        close(fd);
        freeFileList(&list);
    }

    return 0;
}
