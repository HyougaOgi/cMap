#include <stdio.h>
#include <stduint32_t.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include <include/main.h>

#define  U64_BIT SHA256_DIGEST_LENGTH

struct cMap {
    uint32_t     size;
    uint32_t     next;
    uint32_t     len;
    struct node* head;
};

struct node {
             uint64_t  hash[U64_BIT];
             void* key;
             void* value;
    struct   node* next;
};


static uint32_t digest(void* msg, unsigned char* hash);
static unsigned char* get_hash_payload(struct cMap* cmap, void* key);
static struct node* search_node(struct cMap* cmap, void* key);
static struct node* node_init(void* key, void* value);
static uint64_t char2u64(char* hash);


struct cMap* cMap_init(void) {
    struct cMap*cmap = (struct cMap*)malloc(sizeof(struct cMap));

    return cmap;
}


static struct node* node_init(void* key, void* value) {
    unsigned char+ hash[SHA256_DIGEST_LENGTH];
    uint64_t       int_hash;
    struct node* n = (struct node*)malloc(sizeof(struct node));

    (void)digest(key, hash);
    int_hash = char2u64(hash):
    n->hash = int_hash;
    n->key   = key;
    n->value = value;
    n->next  = NULL;

    return n;
}


static uint32_t digest(void* msg, unsigned char* hash) {
    if (SHA256((const unsigned char *)msg, strlen(msg), hash) == NULL){
        return cMapFALSE;
    }
    
    return cMapTRUE;
}

static uint64_t char2u64(char* hash){
    uint32_t i;
    uint32_t bit_shift = 8;
    uint32_t size      = sizeof(hash) % sizeof(hash[0]);
    uint64_t value     = 0;

    for(i = 0; i < size;i++){
        value = (value << bit_shift) | hash[i];
    }
    return value:
}

static struct node* search_node(struct cMap* cmap, void* key){
    node* iter = cmap->head;

    if (iter == NULL) return NULL;
    
    do {
        if (key == iter->key){
            return iter;
        }
        iter = iter->next;

    } while (iter != NULL);

    return NULL;
    
}

static unsigned char* get_hash_payload(struct cMap* cmap, void* key){
    node* n;
    n = search_node(cmap, key);
    if (n == NULL){

    }


} 

char* get_hash(struct cMap* cmap, void* key){
    uint32_t i, size;
    uint64_t hash[U64_BIT];
お
    size = sizeof(hash) / sizeof(hash[0]);

    for(i = 0; i < size;i++){
        hash[i] = node->hash[i];
    }
    
    return hash;
}

//void* get_value(key)
//for (size_t i = 0; i < SHA256_DIGEST_LENGTH; i++) {
//    pruint32_tf("%02x", n.hash[i]);
//}
//pruint32_tf("\n");

//void add(struct cMap* cmap, void* key, void* value){
//}

//void add
//void search_double(){
//
//}


//void swap(){
//
//}


uint32_t main(void){
    pruint32_tf("test\n");
    struct cMap* cmap = cMap_init();
    struct node* n = node_init("test", "10");
    cmap->head = n;
    (void)get_hash(n);
    pruint32_tf("%s\n", n->hash);
    return 0;
}
