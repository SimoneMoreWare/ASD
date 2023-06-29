#include "ST.h"

struct symbleTable{
    Vertice *vertici;
    int size, maxD;
};



ST STinit(int max){
    ST st;
    st=(ST)malloc(sizeof(struct symbleTable));
    if(st==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    st->maxD=1;
    st->size=0;
    st->vertici=(Vertice*)malloc(st->maxD*sizeof(Vertice));
    if(st->vertici==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    return st;
}


void STinsert(ST st, Vertice v){
    if(st->size==st->maxD){
        st->maxD=2*st->maxD;
        st->vertici=realloc(st->vertici, st->maxD*sizeof(Vertice));
        if(st->vertici==NULL){
            printf("Errore di allocazione.");
            exit(EXIT_FAILURE);
        }
    }
    st->vertici[st->size]=v;
    (st->size)++;
    return;
}


Vertice *STsearchByIndex(ST st, int index){
    return &st->vertici[index];
}


int STsearchByName(ST st, char *nome){
    int i;
    for(i=0; i<st->size; i++){
        if(strcmp(st->vertici[i].nome, nome)==0)
            return i;
    }
    return -1;
}


void STfree(ST st){
    if(st!=NULL){
        if(st->vertici!=NULL){
            free(st->vertici);
        }
        free(st);
    }
    return;
}
