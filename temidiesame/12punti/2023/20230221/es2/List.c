#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo *link;

struct nodo{
    int valore;
    link next;
    link pre;
};

struct LIST_L{
    link head;
};
link NEW(int n,link next,link pre);


LIST init(){
    LIST l=malloc(sizeof(*l));

    l->head=NULL;
    return l;

}

link NEW(int n,link next,link pre){
    link x=malloc(sizeof(*x));
    x->valore=n;
    x->pre=pre;
    x->next=next;
    return x;

}

void insertList(LIST l,int n){
    link x=malloc(sizeof(*x));
    link p=malloc(sizeof(*p));

    if(l->head==NULL){
        l->head=NEW(n,NULL,NULL);
    }
    else{
        for(x=l->head;x!=NULL;p=x,x=x->next);
        x=NEW(n,NULL,p);
        p->next=x;
    }


}


void printList(LIST l){
    link x=malloc(sizeof(*x));
    for(x=l->head;x!=NULL;x=x->next)
        printf("%d -",x->valore);
    printf("\n");
}


void f(LIST l,int a,int b){
    link x=malloc(sizeof(*x));
    link p=malloc(sizeof(*p));
    int tmp;

    if(l->head==NULL)
        return;



   if(l->head==NULL)
        return;
    else{
        for(x=l->head;x!=NULL;x=x->next){
            if(x->valore>=a && x->valore<=b){
                if(x==l->head){
                    l->head=x->next;
                    x->next->pre=NULL;
                }else if(x->next==NULL){
                    x->pre->next=NULL;
                }else{
                    x->pre->next=x->next;
                    x->next->pre=x->pre;;
                }
            }


    }
    }

}
