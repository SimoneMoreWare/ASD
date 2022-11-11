//
// Created by simone on 11/11/22.
//

#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>

linkP newNode(linkP head, int newval);


linkP newNode(linkP head, int newval){
    linkP nuovo= malloc(sizeof(* nuovo));
    if(nuovo==NULL) return 0;
    nuovo->val=newval;
    nuovo->next=head;
    return nuovo;
}

void listInsHeadP(linkP (*head),int newval){
    (*head)=newNode((*head),newval);
}

void listDisplayP(linkP p){
    printf("\n");
    while(p!=NULL){
        printf("%d ",p->val);
        printf("%p\n",p->next);
        p=p->next;
    }
}
