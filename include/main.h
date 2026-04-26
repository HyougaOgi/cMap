#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>

#define CMAPTRUE  1
#define CMAPFALSE 0

#define CMAPNULL  0
#define NODENULL  0
#define HASHNULL  0

struct cMap* cMap_init(void);
uint32_t cMap_death(struct cMap* cmap);
char*        get_hash(void* key);
void disp_hash(struct cMap* cmap, void* key);


#endif
