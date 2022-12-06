#ifndef PGLIST_H_DEFINED
#define PGLIST_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "pg.h"

/* ADT di prima classe collezione di personaggi */
typedef struct pgList_s *pgList_t;

/* creatore e distruttore */
pgList_t pgList_init();
void pgList_free(pgList_t pgList);

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList);
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray);

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg);
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod);
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod);

/* Si possono aggiungere altre funzioni se ritenute necessarie */

#endif
