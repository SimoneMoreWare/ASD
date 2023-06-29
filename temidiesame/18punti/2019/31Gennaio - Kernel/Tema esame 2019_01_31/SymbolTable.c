#include "SymbolTable.h"

struct symboltable {
    item *vertici;
    int size, M;
};

ST STinit(int nmax) {
    ST st = malloc(sizeof(*st));
    if (st==NULL) {
        printf("Errore!!\n");
        exit(-1);
    }
    st->size = 0;
    st->M = nmax;
    st->vertici = malloc(nmax *sizeof(item));
    return st;
}




item STsearchbyIndex(ST st, int index) {
    return st->vertici[index];
}




int STsearchbyname(ST st, char *name) {
    int i;
    for(i=0;i<st->size;i++) {
        if (strcmp(name, st->vertici[i].nome)==0)
            return i;
    }
    return -1;
}




int STcount(ST st) {
    return st->size;
}




void STinsert(ST st, item vertice) {
    int i;
    if (st->size == st->M) {
        st->M = 2 * st->M;
        st->vertici = realloc(st->vertici, st->M *sizeof(item));


    }
    i = st->size;
    while (i>0 && strcmp(vertice.nome, st->vertici[i-1].nome)<0) {
        st->vertici[i] = st->vertici[i-1];
        i--;
    }
    st->vertici[i] = vertice;
    st->size++;
    return;
}




item ITEMcrea(char *nome) {
    item i;
    strcpy(i.nome, nome);
    return i;
}




void STfree(ST st){
    if(st!=NULL){
        if(st->vertici!=NULL)
            free(st->vertici);
        free(st);
    }
}
