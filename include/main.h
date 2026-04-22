#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

#define cMapTRUE 1
#define cMapFALSE 0


struct cMap* cMap_init(void);
char*        get_hash(void* key);


#endif
