#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include <include/main.h>

#define  U32BIT SHA256_DIGEST_LENGTH
#define  HASH_SIZE 8


struct cMap {
//    uint32_t     size;
//    uint32_t     next;
    uint32_t     len;
    struct node* head;
};

struct node {
             uint32_t*  hash;
             void*      key;
             void*      value;
    struct   node*      next;
};

static void allc_free(void* data);
static void dynamic_allc_cmap(struct cMap* cmap, uint32_t size);
static uint32_t sha256_bytes_to_u32(unsigned char* char_hash, uint32_t* uint_hash);
static void compute_key_hash(void* msg, uint32_t* hash);
static void dynamic_allc_32(uint32_t* data, uint32_t size);
static uint32_t sha256_digest(void* msg, unsigned char* hash);
//static unsigned char* get_hash_payload(struct cMap* cmap, void* key);
//static struct node* search_node(struct cMap* cmap, void* key);
static uint32_t cmap_head_free(struct node* head);
static struct node* search_node(struct cMap* cmap, void* key);
static struct node* node_init(void* key, void* value);
static uint32_t node_free(struct node* n);
//static uint64_t char2u64(char* hash);


struct cMap* cmap_init(void) {
    struct cMap* cmap;
    dynamic_allc_cmap(cmap, 0);
    cmap->head = NULL;
    cmap->len  = 0;

    return cmap;
}


static struct node* node_init(void* key, void* value) {
    //uint32_t*      hash = (uint32_t*)malloc(sizeof(uint32_t) * 8);
    struct node* n;
    uint32_t* hash;

    dynamic_allc_node(n, 0);
    dynamic_allc_32(hash, HASH_SIZE);

    (void)compute_key_hash(key, hash);
 //    int_hash = char2u64(hash):
    n->hash  = hash;
    n->key   = key;
    n->value = value;
    n->next  = NULL;

    return n;
}

uint32_t cmap_free(struct cMap* cmap){
    if (cmap == NULL){
        printf("cMap is NULL\n");
        return CMAPNULL;
    }
    cmap_head_free(cmap->head);
    free(cmap);
    printf("complete destruct\n");

    return CMAPTRUE;
}

static uint32_t node_free(struct node* n){
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

static uint32_t cmap_head_free(struct node* head){
    if(head == NULL){
#ifdef DEBUG
        printf(head is NULL);
#endif
        return NODENULL;
    }

    struct node* iter      = head;
    struct node* next_node = iter->next;

    while (iter != NULL){
        node_free(iter);
        iter = next_node;
        if (next_node != NULL){
            next_node = next_node->next;
        }
    }

    return CMAPTRUE;
}

// little
static uint32_t sha256_digest(void* msg, unsigned char* hash) {
    if (SHA256((const unsigned char *)msg, strlen(msg), hash) == NULL){
        return CMAPFALSE ;
    }
    
    return CMAPTRUE;
}

static uint32_t sha256_bytes_to_u32(unsigned char* char_hash, uint32_t* uint_hash){
    memcpy(uint_hash, char_hash, SHA256_DIGEST_LENGTH);

    return CMAPTRUE;
}

static uint32_t compute_key_hash(void* msg, uint32_t* hash){
    unsigned char tmp[SHA256_DIGEST_LENGTH];

    if(sha256_digest(msg, tmp) != CMAPTRUE){
        // do nothing
    }
    if(sha256_bytes_to_u32(tmp, hash) != CMAPTRUE){
        // do nothing
    }

    return CMAPTRUE;
}

void cmap_print_hash(struct cMap* cmap, void* key){
    uint32_t i;
    struct node* n = search_node(cmap, key);
    uint32_t* hash = n->hash;
    uint32_t hash_size = sizeof(hash) / sizeof(hash[0]);

    for(i = 0; i < hash_size;i++){
        printf("%0xx", hash[i]);
    }
    printf("\n");
}


static void dynamic_allc_32(uint32_t* data, uint32_t size){
    if(data == NULL){
        data = (uint32_t*)malloc(sizeof(uint32_t) * size);
    } 
}

static void dynamic_allc_cmap(struct cMap* cmap, uint32_t size){
    (void)size;
    if (cmap == NULL){
        struct cMap* cmap = (struct cMap*)malloc(sizeof(struct cMap));
    }
}

static void dynamic_allc_node(struct node* n, uint32_t size){
    (void)size;
    if (n == NULL){
        n = (struct node*)malloc(sizeof(struct node));
    }
}

static void allc_free(void* data){
    if(data == NULL){
        free(data);
    }
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
        (void)compute_key_hash(iter->key, comp_hash);
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
    struct cMap* cmap = cmap_init();
    struct node* n = node_init("test", "10");
    cmap->head = n;
//    (void)get_hash(n);
    cmap_print_hash(cmap, "test");
    cmap_free(cmap);
    return 0;
}
