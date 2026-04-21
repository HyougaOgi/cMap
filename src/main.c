#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include <include/main.h>


struct cMap {
    int   size;
    int   next;
    int   len;
    struct node* head;
};

struct node {
             char  hash[SHA256_DIGEST_LENGTH];
             void* key;
             void* value;
    struct   node* next;
};


static int digest(void* msg, unsigned char* hash);
static struct node* node_init(void* key, void* value);


struct cMap* cMap_init(void) {
    struct cMap*cmap = (struct cMap*)malloc(sizeof(struct cMap));

    return cmap;
}


static struct node* node_init(void* key, void* value) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    struct node* n = (struct node*)malloc(sizeof(struct node));

    digest(key, hash);
    memcpy(n->hash, hash, SHA256_DIGEST_LENGTH);
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

// index and key

char* get_hash(void* key){
    int i, size;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    size = sizeof(hash) / sizeof(hash[0]);

    for(i = 0; i < size;i++){
        hash[i] = node->hash[i];
    }
    
    return hash;
}


//void* get_value(key)
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
    (void)get_hash(n);
    printf("%s\n", n->hash);
    return 0;
}
