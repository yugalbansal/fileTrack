#include "hash.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <openssl/sha.h>

int hashFile(char *path, char *hash) {

    int fd = open(path, O_RDONLY);

    if(fd == -1) {
        return -1;
    }

    SHA256_CTX ctx;

    SHA256_Init(&ctx);

    char buffer[4096];

    int bytesRead;

    while((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {

        SHA256_Update(&ctx, buffer, bytesRead);
    }

    unsigned char result[SHA256_DIGEST_LENGTH];

    SHA256_Final(result, &ctx);

    close(fd);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {

        sprintf(hash + (i * 2), "%02x", result[i]);
    }

    hash[64] = '\0';

    return 0;
}