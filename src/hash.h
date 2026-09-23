#ifndef HASH_H
#define HASH_H

#include "file.h"

int hashFile(char *path, char *hash);
void calculateTreeHash(Node *node);

#endif