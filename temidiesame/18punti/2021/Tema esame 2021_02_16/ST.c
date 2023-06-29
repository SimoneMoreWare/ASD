#include "ST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct symbleTable{
    Argomento *argomenti;
    int maxD, dim;
};


ST STinit(int maxD){
    ST st;
    st=(ST)malloc(sizeof(struct symbleTable));
    if(st==NULL)
        exit(EXIT_FAILURE);
    st->maxD=maxD;
    st->dim=0;
    st->argomenti=(Argomento *)malloc(st->maxD*sizeof(Argomento));
    if(st->argomenti==NULL)
        exit(EXIT_FAILURE);
    return st;
}


void STinsert(ST st, Argomento a){
    if(st->maxD==st->dim){
        st->maxD=2*st->maxD;
        st->argomenti=realloc(st->argomenti, st->maxD*sizeof(Argomento));
        if(st->argomenti==NULL)
            exit(EXIT_FAILURE);
    }
    st->argomenti[st->dim]=a;
    (st->dim)++;
    return;
}


int STcount(ST st){
    return st->dim;
}


int STsearch(ST st, char *nome){
    int i;
    for(i=0; i<st->dim; i++){
        if(strcmp(nome, st->argomenti[i].nome)==0)
            return i;
    }
    return -1;
}


void STfree(ST st){
    if(st!=NULL){
        if(st->argomenti!=NULL)
            free(st->argomenti);
        free(st);
    }
    return;
}
