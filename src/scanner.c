#define _DEFAULT_SOURCE
#include "scanner.h"
#include "file.h"
#include "hash.h"

#include <stdio.h>
#include <dirent.h>
#include <string.h>

void ReadDirectory(char *path, FileList *list)
{
    // now open dir
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        printf("Could not open directory");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // case - ignore . .. .ft
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, ".ft") == 0)
        {

            continue;
        }

        // check it is file or directory
        if (entry->d_type == DT_REG)
        {

            char filePath[1000];
            char hash[65];
            snprintf(filePath, sizeof(filePath),
                     "%s/%s", path, entry->d_name);

            if (hashFile(filePath, hash) == 0)
            {
                addFile(list, filePath, hash);
            }
        }
        else if (entry->d_type == DT_DIR)
        {
            char newPath[1000];
            snprintf(newPath, sizeof(newPath), "%s/%s", path, entry->d_name);
            ReadDirectory(newPath, list);
        }
    }
    // close dir
    closedir(dir);
}