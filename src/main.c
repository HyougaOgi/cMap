#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include <include/main.h>

#define  U32BIT SHA256_DIGEST_LENGTH

struct cMap {
    uint32_t     size;
    uint32_t     next;
    uint32_t     len;
    struct node* head;
};

struct node {
             uint32_t*  hash;
             void*      key;
             void*      value;
    struct   node*      next;
};

static uint32_t conversion_hash_char2uint32(unsigned char* char_hash, uint32_t* uint_hash);
static void create_hash(void* msg, int* hash);
static uint32_t digest(void* msg, unsigned char* hash);
//static unsigned char* get_hash_payload(struct cMap* cmap, void* key);
//static struct node* search_node(struct cMap* cmap, void* key);
static uint32_t head_death(struct node* head);
static struct node* search_node(struct cMap* cmap, void* key);
static struct node* node_init(void* key, void* value);
static uint32_t node_death(struct node* n);
//static uint64_t char2u64(char* hash);


struct cMap* cMap_init(void) {
    struct cMap*cmap = (struct cMap*)malloc(sizeof(struct cMap));

    return cmap;
}


static struct node* node_init(void* key, void* value) {
    uint32_t*      hash = (uint32_t*)malloc(sizeof(uint32_t) * 8);
    struct node*   n    = (struct node*)malloc(sizeof(struct node));

    create_hash(key, hash);
 //    int_hash = char2u64(hash):
    n->hash  = hash;
    n->key   = key;
    n->value = value;
    n->next  = NULL;

    return n;
}

uint32_t cMap_death(struct cMap* cmap){
    if (cmap == NULL){
        printf("cMap is NULL\n");
        return CMAPNULL;
    }

    head_death(cmap->head);
    free(cmap);
    printf("complete destruct\n");

    return CMAPTRUE;
}

static uint32_t node_death(struct node* n){
    if(n == NULL){  
#ifdef DEBUG
        printf("node is NULL\n");
#endif

        return NODENULL;
    }
    if(n->hash == NULL){
#ifdef DEBUG
        printf("hash is NULL\n");
#endif

        return HASHNULL;
    }

    free(n->hash);
    free(n);

#ifdef DEBUG
    printf("hash is NULL\n");
#endif

    return CMAPTRUE;
}

static uint32_t head_death(struct node* head){
    if(head == NULL){
#ifdef DEBUG
        printf(head is NULL);
#endif
        return NODENULL;
    }

    struct node* iter      = head;
    struct node* next_node = iter->next;

    while (iter != NULL){
        node_death(iter);
        iter = next_node;
        if (next_node != NULL){
            next_node = next_node->next;
        }
    }

    return CMAPTRUE;
}

// little
static uint32_t digest(void* msg, unsigned char* hash) {
    if (SHA256((const unsigned char *)msg, strlen(msg), hash) == NULL){
        return CMAPFALSE ;
    }
    
    return CMAPTRUE;
}

static uint32_t conversion_hash_char2uint32(unsigned char* char_hash, uint32_t* uint_hash){
    memcpy(uint_hash, comp_hash, SHA256_DIGEST_LENGTH);

    return CMAPTRUE;
}

static uint32_t create_hash(void* msg, int* hash){
    unsigned char tmp[SHA256_DIGEST_LENGTH];

    if(digest(msg, tmp) != CMAPTRUE){
        // do nothing
    }
    if(conversion_hash_char2uint32(tmp, hash) != CMAPTRUE){
        // do nothing
    }
}

void disp_hash(struct cMap* cmap, void* key){
    uint32_t i;
    struct node* n = search_node(cmap, key);
    uint32_t* hash = n->hash;
    uint32_t hash_size = sizeof(hash) / sizeof(hash[0]);

    for(i = 0; i < hash_size;i++){
        printf("%0xx", hash[i]);
    }
    printf("\n");
}
//static uint64_t char2u64(char* hash){
//    uint32_t i;
//    uint32_t bit_shift = 8;
    //    uint32_t size     = sizeof(hash) % sizeof(hash[0]);
//    uint64_t value     = 0;
//
//    for(i = 0; i < size;i++){
//        value = (value << bit_shift) | hash[i];
//    }
//    return value:
//}

static struct node* search_node(struct cMap* cmap, void* key){
    if (cmap->head == NULL) return NULL;

    struct node*    iter = cmap->head;
    uint32_t comp_hash[8];

    while (iter != NULL){ 
        (void)digest(iter->key, comp_hash);
        if (key == iter->key && iter->hash == comp_hash){
            return iter;
        }
        iter = iter->next;
    }

    return NULL;
    
}

//static unsigned char* get_hash_payload(struct cMap* cmap, void* key){
//    node* n;
//    n = search_node(cmap, key);
//    if (n == NULL){
//
//    }
//
//
//} 
//
//char* get_hash(struct cMap* cmap, void* key){
//    uint32_t i, size;
//    uint64_t hash[U64_BIT];
//
//    size = sizeof(hash) / sizeof(hash[0]);
//
//    for(i = 0; i < size;i++){
//        hash[i] = node->hash[i];
//    }
//    
//    return hash;
//}

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


int main(void){
    printf("test\n");
    struct cMap* cmap = cMap_init();
    struct node* n = node_init("test", "10");
    cmap->head = n;
//    (void)get_hash(n);
    disp_hash(cmap->head);
    cMap_death(cmap);
    return 0;
}
