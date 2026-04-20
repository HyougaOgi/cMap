#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include <include/main.h>

static int digest(void* msg, unsigned char* hash);
static struct node* node_init(void* key, void* value);


struct cMap* cMap_init(void) {
    struct cMap*cmap = (struct cMap*)malloc(sizeof(struct cMap));
    return cmap;
}

static struct node* node_init(void* key, void* value) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    digest(key, hash);
    struct node* n = (struct node*)malloc(sizeof(struct node));
    memcpy(&n->hash, &hash, SHA256_DIGEST_LENGTH);
    n->key   = key;
    n->value = value;
    n->next  = NULL;
    return n;
}


static int digest(void* msg, unsigned char* hash) {
    if (SHA256((const unsigned char *)msg, strlen(msg), hash) == NULL){
        return cMapFALSE;
    }
    return cMapTRUE;
}


//unsigned char getHash();
//for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//    printf("%02x", n.hash[i]);
//}
//printf("\n");

//void add(struct cMap* cmap, void* key, void* value){
//}

//void add
//void search_double(){
//
//}


//void swap(){
//
//}


int main(void){
    printf("test\n");
    struct cMap* cmap = cMap_init();
    struct node* n = node_init("test", "10");
    cmap->head = n;
    return 0;
}
