#include "pgList.h"


/* ADT di prima classe collezione di personaggi */
struct pgList_s {
    pg_t pg;
    pgList_t next;
};

/* creatore e distruttore */
pgList_t pgList_init() {
    pgList_t pgList = NULL;
    return pgList;
}
void pgList_free(pgList_t pgList) {
    pgList_t tmp;
    while(pgList != NULL) {
        tmp = pgList;
        pgList = pgList->next;
        free(tmp);
    }
    free(pgList);
}

/* lettura e scrittura su file */
pgList_t pgList_read(FILE *fp, pgList_t pgList) {
    pg_t tmp;
    while(!feof(fp)) {
        if(pg_read(fp, &tmp))
            pgList = pgList_insert(pgList, tmp);
    }
    return pgList;
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    pgList_t tmp;
    for(tmp = pgList; tmp != NULL; tmp = tmp->next)
        pg_print(fp, &(tmp->pg), invArray);
}

/* inserimento di un nuovo personaggio */
pgList_t pgList_insert(pgList_t pgList, pg_t pg) {
    pgList_t insert = (pgList_t) malloc(sizeof(pgList_i));
    insert->pg = pg;
    insert->next = pgList;
    pgList = insert;
    return pgList;
}
/* cancellazione con rimozione */
pgList_t pgList_remove(pgList_t pgList, char* cod) {
    pgList_t tmp, prec = NULL;
    for(tmp = pgList; tmp != NULL; prec = tmp, tmp = tmp->next) {
        if(strcmp(tmp->pg.cod, cod) == 0) {
            if(prec != NULL) 
                prec->next = tmp->next;
            else {
                pgList = tmp->next;
            }
            tmp->next = NULL;
            pgList_free(tmp);
            break;
        }
    }
    return pgList;
}

/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod) {
    pgList_t tmp;
    for(tmp = pgList; tmp != NULL; tmp = tmp->next) {
        if(strcmp(tmp->pg.cod, cod) == 0) {
            return &(tmp->pg);
        }
    }
    return NULL;
}
