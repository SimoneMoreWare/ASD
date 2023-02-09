/*
 * inversione lista
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
    int val;
    link next;
};

link newNode(int val,link next);
void printlist(link head);
link invertilista(link head,link headinv);
int main(){
    link head=NULL;
    head= newNode(6,head);
    head= newNode(5,head);
    head= newNode(4,head);
    head= newNode(3,head);
    head= newNode(2,head);
    head= newNode(1,head);
    printlist(head);
    link headinv=NULL;
    headinv=invertilista(head,headinv);
    printlist(headinv);
    return 0;
}

link newNode(int val,link next){
    link new = malloc(sizeof *new);
    if(new==NULL){
        return NULL;
    }else{
        new->val=val;
        new->next=next;
    }
    return new;
}

void printlist(link head){
    printf("\n");
    link tmp=head;
    while(tmp->next!=NULL){
        printf("%d->",tmp->val);
        tmp=tmp->next;
    }
    printf("%d",tmp->val);
}

link invertilista(link head,link headinv){
    //inserimento in testa
    link tmp=head;
    while(tmp!=NULL){
        headinv=newNode(tmp->val,headinv);
        tmp=tmp->next;
    }
    return headinv;
}

