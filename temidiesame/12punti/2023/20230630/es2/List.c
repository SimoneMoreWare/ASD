
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
    int n;
    link next;
};

struct LIST_L{
    link head;
};

link NEW(int n,link next);

LIST init(){
    LIST l=malloc(sizeof(*l));
    l->head=NULL;
    return l;
}

link NEW(int n,link next){
    link x=malloc(sizeof(*x));
    x->n=n;
    x->next=next;
    return x;
}

void insertList(LIST l,int n){
    link x=malloc(sizeof(*x));
    link p=malloc(sizeof(*p));

    if(l->head==NULL)
        l->head=NEW(n,NULL);
    else{
    for(x=l->head;x!=NULL;p=x,x=x->next);
        x=NEW(n,NULL);
        p->next=x;
    }

}


void printList(LIST l){
    link x=malloc(sizeof(*x));
    for(x=l->head;x!=NULL;x=x->next)
        printf("%d ->",x->n);
    printf("\n");

}


void f(LIST l){
    int cnt;
    link x;
    link p=NULL;;

    for(x=l->head,cnt=0;x!=NULL;x=x->next,cnt++){
        if(cnt%3==0){
            if(x==l->head){
                l->head=x->next;
            }else{
                p->next=x->next;
            }

        }else{
            p=x;
        }


    }


}




