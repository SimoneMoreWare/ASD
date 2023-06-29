#include "ST.h"

struct symbleTable{
   Vertice *vertici;
   int size, maxD;
};



//VERTICE
Vertice VERTICEcrea(char *nome){
    Vertice v;
    strcpy(v.nome, nome);
    return v;
}



//ST
ST STinit(int max){
    ST st;
    st=(ST)malloc(sizeof(struct symbleTable));
    if(st==NULL) exit(EXIT_FAILURE);
    st->size=0;
    st->maxD=max;
    st->vertici=(Vertice*)malloc(st->maxD*sizeof(Vertice));
    if(st->vertici==NULL) exit(EXIT_FAILURE);
    return st;
}


void STinsert(ST st, Vertice a){
    if(st->maxD==st->size){
        st->maxD=2*st->maxD;
        st->vertici=realloc(st->vertici, st->maxD*sizeof(Vertice));
        if(st->vertici==NULL) exit(EXIT_FAILURE);
    }
    st->vertici[st->size]=a;
    (st->size)++;
    return;
}


Vertice STgetVerticeByIndex(ST st, int index){
    return st->vertici[index];
}


int STsearch(ST st, char *nome){
    int i;
    for(i=0; i<st->size; i++){
        if(strcmp(st->vertici[i].nome, nome)==0)
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
