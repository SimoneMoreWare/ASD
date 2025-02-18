#include <string.h>

#ifndef mod_stats
    #define mod_stats 
    #include "stats.h"
#endif

#define fileNameINV "inventario.txt"
#define MAX_LENGTH_ITEM 50

typedef struct inv_t {
    int usingItem;
    char name[MAX_LENGTH_ITEM];
    char type[MAX_LENGTH_ITEM];
    stats *stat;
} item;

typedef struct tabInv_t {
    item **vettInv;
    int nInv;
    int maxInv;
} tabInv;

item* ITEMget(char *name, char *type, int hp, int mp, int atk, int def, int mag, int spr);

item* ITEMsearch(tabInv inv, char *name);

void ITEMprint(item item);

void ITEMfree(item* item);

tabInv* TABINVinit();

void TABINVfree(tabInv* tab);