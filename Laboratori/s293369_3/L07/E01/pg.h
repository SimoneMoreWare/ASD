#ifndef PG_H_DEFINED
#define PG_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"

/* quasi ADT personaggio; si noti che si tratta di un composto con riferimento 
a un equipArray di proprieta' */
typedef struct pg_s {
    char cod[LEN];
    char nome[LEN];
    char classe[LEN];
    stat_t b_stat, eq_stat;
    equipArray_t equip;
} pg_t;

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp);
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp);

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray);
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario:
di fatto e' sufficiente chiamare l'opportuna funzione dal modulo equipArray */
void pg_updateEquip(pg_t *pgp, invArray_t invArray);

/* Si possono aggiungere altre funzioni se ritenute necessarie */
void pg_updateStat(pg_t *pgp, invArray_t invArray);

#endif
