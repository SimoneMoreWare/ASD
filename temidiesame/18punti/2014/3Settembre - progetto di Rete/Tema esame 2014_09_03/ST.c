#include "ST.h"

struct symbleTable{
    Vertice *vertici;
    int dim, maxD;
};



ST STinit(int max){
    ST st;
    st=(ST)malloc(sizeof(struct symbleTable));
    if(st==NULL) exit(EXIT_FAILURE);
    st->dim=0;
    st->maxD=max;
    st->vertici=(Vertice*)malloc(max*sizeof(Vertice));
    if(st->vertici==NULL) exit(EXIT_FAILURE);
    return st;
}


void STinsert(ST st, Vertice v){
    if(st->dim==st->maxD){
        st->maxD=2*st->maxD;
        st->vertici=realloc(st->vertici, st->maxD*sizeof(Vertice));
        if(st->vertici==NULL) exit(EXIT_FAILURE);
    }
    st->vertici[st->dim]=v;
    (st->dim)++;
    return;
}


int STsearch(ST st, char *vertice){
    int i;
    for(i=0; i<st->dim; i++){
        if(strcmp(vertice, st->vertici[i].nome)==0)
            return i;
    }
    return -1;
}


Vertice *STgetVerticeByIndex(ST st, int index){
    return &st->vertici[index];
}


void STfree(ST st){
    if(st!=NULL){
        if(st->vertici!=NULL)
            free(st->vertici);
        free(st);
    }
    return;
}
