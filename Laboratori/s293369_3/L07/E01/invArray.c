//
// Created by simone on 06/12/22.
//

#include "invArray.h"
struct invArray_s {
    int n;
    inv_t *inv;
};
invArray_t invArray_init(){
    invArray_t array = malloc(sizeof(* array));
    array->n=0;
    return array;
}

void invArray_read(FILE *fp, invArray_t invArray){
    int i;
    fscanf(fp,"%d",&(invArray->n));
    invArray->inv=malloc((invArray->n)*sizeof(inv_t));
    for(i=0;i<invArray->n;i++) inv_read(fp,&(invArray->inv[i]));
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i;
    for(i=0;i<invArray->n;i++){
        fprintf(fp,"%d\t",i);
        inv_print(fp,&(invArray->inv[i]));
    }
    fprintf(fp,"Numero oggetti in inventario: %d\n\n",invArray->n);

}

void invArray_free(invArray_t invArray) {
    if(invArray != NULL && invArray->inv != NULL)
        free(invArray->inv);

    if(invArray != NULL)
        free(invArray);
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
    inv_print(fp,&(invArray->inv[index]));
}

inv_t *invArray_getByIndex(invArray_t invArray, int index) {
    return &(invArray->inv[index]);
}

/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name) {
    int i;

    for(i = 0; i < invArray->n; i++) {
        if(strcmp(name,invArray->inv[i].nome) == 0)
            return i;
    }

    return -1;
}
