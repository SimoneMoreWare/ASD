#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
    char c;
    link next;
    link pre;
};

struct LIST_L{
    link root;
};
link NEW(char c,link pre,link next);


void printList(LIST l){
    link x;
    for(x=l->root;x!=NULL;x=x->next)
        printf("%c ",x->c);
    printf("\n");
}

LIST init(){
    LIST l=malloc(sizeof(*l));
    l->root=NULL;
    return l;
}

link NEW(char c,link pre,link next){
    link x=malloc(sizeof(*x));
    x->c=c;
    x->next=next;
    x->pre=pre;
    return x;
}

void insertList(LIST l){
    int N=8;
    int i;
    link x,p;
    char vett[8]={'a','a','b','b','c','d','d','d'};

    for(i=0;i<N;i++){

    if(l->root==NULL){ //root
    l->root=NEW(vett[i],NULL,NULL);
    }else{
    for(x=l->root,p=NULL;x!=NULL;p=x,x=x->next);
    x=NEW(vett[i],p,NULL);
    p->next=x;
    }
    }

    printList(l);
}



void f(LIST l,int k){
    link x,f;
    int cnt,flag;

     if(l->root==NULL)
            return;

        else{
            for(x=l->root;x!=NULL;x=x->next){
                if(x->next!=NULL && x->next->c==x->c){
                    cnt=0;
                    for(f=x,cnt=0;f!=NULL && f->c==x->c;cnt++,f=f->next);
                    if(cnt>=k){
                        x->next=f;
                    }
                }


            }




        }



}


