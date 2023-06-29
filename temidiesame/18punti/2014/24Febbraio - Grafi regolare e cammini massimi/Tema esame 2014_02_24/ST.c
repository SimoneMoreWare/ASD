#include "ST.h"

struct symbolTable{
    Vertice *vertici;
    int size, maxD;
};



ST STinit(int max){
    ST s;
    s=(ST)malloc(sizeof(struct symbolTable));
    if(s==NULL) exit(EXIT_FAILURE);
    s->maxD=max;
    s->size=0;
    s->vertici=(Vertice*)malloc(max*sizeof(Vertice));
    if(s->vertici==NULL) exit(EXIT_FAILURE);
    return s;
}


void STinsert(ST st, Vertice v){
    if(st->size==st->maxD){
        st->maxD=2*st->maxD;
        st->vertici=realloc(st->vertici, st->maxD*sizeof(Vertice));
        if(st->vertici==NULL) exit(EXIT_FAILURE);
    }
    st->vertici[st->size]=v;
    (st->size)++;
    return;
}


Vertice *STgetVerticeByIndex(ST st, int index){
    return &st->vertici[index];
}


int STgetVerticeByLabel(ST st, char *label){
    int i;
    for(i=0; i<st->size; i++){
        if(strcmp(st->vertici[i].vertice, label)==0)
            return i;
    }
    return -1;
}


void STfree(ST st){
    if(st!=NULL){
        if(st->vertici!=NULL)
            free(st->vertici);
        free(st);
    }
    return;
}
