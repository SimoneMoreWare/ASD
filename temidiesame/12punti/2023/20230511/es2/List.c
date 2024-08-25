#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct node *link;

struct node{
    int val;
    link next;
};

struct LIST_l{
    link root;
};

link NEW(int v,link n);

LIST init(){
    LIST l=malloc(sizeof(*l));
    l->root=NULL;
    return l;
}

link NEW(int v,link n){
    link x=malloc(sizeof(*x));
    x->val=v;
    x->next=n;
    return x;
}

LIST insertR(LIST l,int *interi,int N){
    int i=0;
    link x=malloc(sizeof(*x));

    if(l->root==NULL)
        l->root=NEW(interi[i],NULL);

    x=l->root;
    for(i=1;i<N;i++){
    x->next=NEW(interi[i],NULL);
    x=x->next;
    }

    return l;

}

void printL(LIST l){

    link x=malloc(sizeof(*x));
    for(x=l->root;x!=NULL;x=x->next){
        printf("%d",x->val);
        if(x->next!=NULL)
            printf("->");
    }
    printf("\n");

}

void f(LIST l){
    link x,p;

     if(l->root==NULL)
            return;
        else{
            for(x=l->root;x!=NULL;x=x->next){
                if(x->next!=NULL && x->next->val==x->val){
                    for(p=x;p!=NULL && p->val==x->val;p=p->next);
                    if(p==NULL){
                        x->next=NULL;
                    }else{
                        x->next=p;
                    }

                }

            }



        }



}


