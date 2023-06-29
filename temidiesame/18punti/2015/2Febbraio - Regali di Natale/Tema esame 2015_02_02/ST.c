#include "ST.h"

struct symbleTable{
   Amico *amici;
   int size, maxD;
};



ST STinit(int max){
    ST st;
    st=(ST)malloc(sizeof(struct symbleTable));
    if(st==NULL) exit(EXIT_FAILURE);
    st->size=0;
    st->maxD=max;
    st->amici=(Amico*)malloc(st->maxD*sizeof(Amico));
    if(st->amici==NULL) exit(EXIT_FAILURE);
    return st;
}


void STinsert(ST st, Amico a){
    if(st->maxD==st->size){
        st->maxD=2*st->maxD;
        st->amici=realloc(st->amici, st->maxD*sizeof(Amico));
        if(st->amici==NULL) exit(EXIT_FAILURE);
    }
    st->amici[st->size]=a;
    (st->size)++;
    return;
}


Amico *STgetAmicoByIndex(ST st, int index){
    return &st->amici[index];
}


int STsearch(ST st, char *nome){
    int i;
    for(i=0; i<st->size; i++){
        if(strcmp(st->amici[i].nome, nome)==0)
            return i;
    }
    return -1;
}


void STfree(ST st){
    if(st!=NULL){
        if(st->amici!=NULL)
            free(st->amici);
        free(st);
    }
    return;
}
