#ifndef FILE_H
#define FILE_H

typedef struct Node{
    char path[1000];
    char hash[65];
    int isDirectory;

    struct Node **children; // children array of nodes 
    int childCount; // children count 
    int capacity; // size allocated for this array 
} Node;


Node *createNode(char *name, char *hash, int isDirectory);
void addChild(Node *parent, Node *child);
void freeNode(Node *node);

#endif