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

int saveTree(int fd, Node *node){
    char buffer[1100];

    char type;

    if (node->isDirectory) {
        type = 'D';
    }
    else {
        type = 'F';
    }

    int n = snprintf(
        buffer,
        sizeof(buffer),
        "%c %s %s\n",
        type,
        node->path,
        node->hash
    );

    if (write(fd, buffer, n) != n) {
        return -1;
    }

    for (int i = 0; i < node->childCount; i++) {
        if (saveTree(fd, node->children[i]) == -1) {
            return -1;
        }
    }

    return 0;
}