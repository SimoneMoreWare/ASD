#include "ST.h"
#include <string.h>

struct symbletable{
     Stanza *stanze;
     int nStanze, maxD;
};



ST STinit(int max){
    ST st;
    st=(ST)malloc(sizeof(struct symbletable));
    if(st==NULL) exit(EXIT_FAILURE);
    st->nStanze=0;
    st->maxD=max;
    st->stanze=(Stanza*)malloc(st->maxD*sizeof(Stanza));
    if(st->stanze==NULL) exit(EXIT_FAILURE);
    return st;
}


void STinsert(ST st, Stanza s){
    if(st->maxD==st->nStanze){
        st->maxD=2*st->maxD;
        st->stanze=realloc(st->stanze, st->maxD*sizeof(Stanza));
        if(st->stanze==NULL) exit(EXIT_FAILURE);
    }
    st->stanze[st->nStanze]=s;
    (st->nStanze)++;
    return;
}


int STsearch(ST st, char *nome){
    int i;
    for(i=0; i<st->nStanze; i++){
        if(strcmp(nome, STANZAgetNome(&st->stanze[i]))==0){
            return i;
        }
    }
    return -1;
}


Stanza STgetStanza(ST st, int index){
    return st->stanze[index];
}


void STfree(ST st){
    if(st!=NULL){
        if(st->stanze!=NULL){
            free(st->stanze);
        }
        free(st);
    }
    return;
}
