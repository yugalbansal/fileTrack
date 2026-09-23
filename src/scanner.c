#define _DEFAULT_SOURCE

#include "scanner.h"
#include "file.h"
#include "hash.h"

#include <stdio.h>
#include <dirent.h>
#include <string.h>

Node *ReadDirectory(char *path)
{
    DIR *dir = opendir(path);

    if (dir == NULL)
    {
        printf("Could not open directory\n");
        return NULL;
    }

    Node *root = createNode(path, "", 1);

    if (root == NULL)
    {
        closedir(dir);
        return NULL;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, ".ft") == 0)
        {
            continue;
        }

        char newPath[1000];

        snprintf(
            newPath,
            sizeof(newPath),
            "%s/%s",
            path,
            entry->d_name
        );

        if (entry->d_type == DT_REG)
        {
            char hash[65];

            if (hashFile(newPath, hash) == 0)
            {
                Node *file = createNode(
                    newPath,
                    hash,
                    0
                );

                if (file != NULL)
                {
                    addChild(root, file);
                }
            }
        }

        else if (entry->d_type == DT_DIR)
        {
            Node *directory = ReadDirectory(newPath);

            if (directory != NULL)
            {
                addChild(root, directory);
            }
        }
    }

    closedir(dir);

    return root;
}