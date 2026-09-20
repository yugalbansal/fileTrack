#include "hash.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <openssl/sha.h>

// SHA256_Init(...) - used for empty hash creation
// SHA256_Update(...) - used to feed more data to same and then calc hash
// SHA256_Final(...) - used when all data is feed to get final hash
int hashFile(char *path, char *hash)
{
    unsigned char raw[32];
    int fd = open(path, O_RDONLY);
    if (fd == -1)
    {
        perror("cannot open the file");
        return -1;
    }
    SHA256_CTX ctx;
    // init the hash
    SHA256_Init(&ctx);
    unsigned char buffer[4096];
    ssize_t bytes;
    // read the file
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
    {
        // update the hash
        SHA256_Update(&ctx, buffer, bytes);
    }
    if (bytes == -1)
    {
        perror("read");
        close(fd);
        return -1;
    }
    SHA256_Final(raw, &ctx);
    close(fd);
    for(int i=0;i<32;i++){
        sprintf(hash+i*2, "%02x", raw[i]);
    }
    hash[64] = '\0';
    return 0;
}