#include "ST.h"
#include <string.h>

struct symbleTable{
    Vertice *vertici;
    int size, maxD;
};


ST STinit(int maxD){
    ST st;
    st=(ST)malloc(sizeof(struct symbleTable));
    if(st==NULL)
        exit(EXIT_FAILURE);
    st->maxD=maxD;
    st->size=0;
    st->vertici=(Vertice*)malloc(maxD*sizeof(Vertice));
    if(st->vertici==NULL)
        exit(EXIT_FAILURE);
    return st;

}


void STinsert(ST st, Vertice v){
    if(st->maxD==st->size){
        st->maxD=2*st->maxD;
        st->vertici=realloc(st->vertici, st->maxD*sizeof(Vertice));
        if(st->vertici==NULL)
            exit(EXIT_FAILURE);
    }
    st->vertici[st->size]=v;
    (st->size)++;
    return;
}


int STsearch(ST st, char *id){
    int i;
    for(i=0; i<st->size; i++){
        if(strcmp(id, st->vertici[i].id)==0)
            return i;
    }
    return -1;
}


Vertice STgetByIndex(ST st, int index){
    return st->vertici[index];
}


void STfree(ST st){
    if(st!=NULL){
        free(st->vertici);
        free(st);
    }
    return;
}
