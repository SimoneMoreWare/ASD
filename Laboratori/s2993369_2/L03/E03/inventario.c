//
// Created by simone on 11/11/22.
//

#include "inventario.h"
#include <stdlib.h>
#include <stdio.h>

linkO newnode(linkO head,int newval);

linkO newnode(linkO head,int newval){
    linkO nuovo=malloc(sizeof(* nuovo));
    if(nuovo==NULL) return 0;
    nuovo->val=newval;
    nuovo->next=head;
    return nuovo;
}

void listInsHeadO(linkO *head,int newval){
    *head=newnode(*head,newval);
}

void listDisplayO(linkO p){
    printf("\n");
    while(p!=NULL) {
        printf("%d", p->val);
        printf("%p\n", p->next);
        p = p->next;
    }
}
