#ifndef mod_stats
    #define mod_stats
    #include "stats.h"
#endif

#ifndef mod_inv
    #define mod_inv
    #include "inv.h"
#endif

#define fileNamePG "pg.txt"
#define MAX_LENGTH_CODE 6+1
#define MAX_LENGTH_PG 50
#define MAX_ITEMS 8

typedef struct tabEquip_t {
    int usingPG;
    item **vettEq;
} tabEquip;

typedef struct nodoPg_t *link;

typedef struct nodoPg_t {
    char code[MAX_LENGTH_CODE];
    char name[MAX_LENGTH_PG];
    char pgClass[MAX_LENGTH_PG];
    tabEquip *equip;
    stats *stat;
    link next;
} pg;

typedef struct tabPg_t {
    link headPg;
    link tailPg;
    int nPg;
} tabPg;

int PGcodecheck(char *code);

link PGget(char *code, char *nome, char *pgClass, int hp, int mp, int atk, int def, int mag, int spr);

void TABPGfree(tabPg *tab);

tabPg* TABPGinit();

void PGinsert(tabPg *tab, link insert);

link PGsearch(tabPg tab, char *code);

void PGdelete(tabPg *tab, char *code);

void PGprint(tabPg tab, char *code);

void PGgainItem(tabPg *tab, char *code, tabInv inv, char *itemName);

void PGremoveItem(tabPg *tab, char *code, tabInv inv, char *itemName);
