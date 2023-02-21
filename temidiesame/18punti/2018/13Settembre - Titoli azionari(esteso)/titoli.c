#include "titoli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo *link;

struct nodo{
    titolo item;
    link next;
};

struct titoli_{
    link head;
    int n;
};

static link NEWnode(titolo item, link next){
    link t;
    t = malloc(sizeof(*t));
    t->item = item;
    t->next = next;
    return t;
}

titoli titoliInit(){
    titoli t;
    t = malloc(sizeof(titoli));
    t->head = NULL;
    t->n = 0;
    return t;
}

void titoliFree(titoli t){
    link h = t->head;
    while(h != NULL) {
        h = t->head;
        t->head = t->head->next;
        free(h);
    }
}

int listempty(titoli t){
    if(t == NULL || t->head == NULL || t->n == 0)
        return 1;
    return 0;
}

void titoliInsert(titoli list, titolo t){
    link p,x;
    if(list->head == NULL) {
        list->head = NEWnode(t, NULL);
        list->n++;
        //printf("[list] Inserito\n");
    }
    else if(titolocmp(getKey(t),getKey(list->head->item))<0){
        list->head = NEWnode(t, list->head);
        list->n++;
       // printf("[list] Inserito\n");
        return;
    }
    else{
        for(p=list->head,x=list->head->next; x!=NULL && titolocmp(getKey(t),getKey(x->item)) > 0; p=x, x=x->next);
                p->next = NEWnode(t,x);
                list->n++;
                //printf("[list] Inserito\n");
                return;
    }
}

void titoliStore(FILE *out, titoli list){
    link x;
    if(listempty(list))
        return;
    for(x=list->head; x!=NULL; x=x->next)
        titoloStore(out,x->item);
}

titolo titoliSearch(titoli list, char *cod){
    link x;
    for(x = list->head; x!=NULL; x=x->next)
        if(titolocmp(getKey(x->item), cod) == 0)
            return x->item;
    return NULL;
}