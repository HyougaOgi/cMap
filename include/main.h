#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <openssl/sha.h>

#define cMapTRUE 1
#define cMapFALSE 0

struct cMap {
    int   size;
    int   next;
    int   len;
    struct node* head;
};


struct node {
    const unsigned char  hash[SHA256_DIGEST_LENGTH];
    const          void* key;
                   void* value;
    struct         node* next;
};

struct cMap* cMap_init(void);



#endif
