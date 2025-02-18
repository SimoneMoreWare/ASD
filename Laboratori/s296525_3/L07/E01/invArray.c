#include "invArray.h"

/* ADT di prima classe collezione di oggetti di inventario */
struct invArray_s {
    inv_t* inv;
    int N;
};

/* creatore e disruttore */
invArray_t invArray_init() {
    FILE *fp = fopen("inventario.txt", "r");
    invArray_t invArray = (invArray_t) malloc(sizeof(invArray_i));

    invArray_read(fp, invArray);
    
    fclose(fp);
    return invArray;
}

void invArray_free(invArray_t invArray) {
    int i;

    for(i = 0; i < invArray->N; i++) {
        inv_free(&(invArray->inv[i]));
    }
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray) {
    int i;

    fscanf(fp, "%d", &(invArray->N));
    invArray->inv = (inv_t*) malloc(invArray->N*sizeof(inv_t));
    for(i = 0; i < invArray->N; i++) {
        inv_read(fp, &(invArray->inv[i]));
    }
}

void invArray_print(FILE *fp, invArray_t invArray) {
    int i;

    fprintf(fp, "%d\n", invArray->N);
    for(i = 0; i < invArray->N; i++) {
        inv_print(fp, &(invArray->inv[i]));
    }
}

/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
    inv_print(fp, &(invArray->inv[index]));
}

/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t* invArray_getByIndex(invArray_t invArray, int index) {
    return &(invArray->inv[index]);
}

/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name) {
    int i;

    for(i = 0; i < invArray->N; i++) {
        if(strcmp(invArray->inv[i].nome, name) == 0)
            return i;
    }

    return -1;
}

