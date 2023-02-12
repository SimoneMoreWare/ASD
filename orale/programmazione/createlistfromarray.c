/*
 * Generare un ADT di I classe Lista e creare una funzione che scandisce un vettore di interi
 * e riporta in una nuova lista gli elementi del vettore con lo stesso ordine.
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct node *link;

struct node{
    int val;
    link next;
};

link newNode(link next,int val);
link insTail(link head,int val);
void printlist(link head);

int main(){
    int val[] = {1,2,3,4,19,6,7,8,9};
    int n=9;
    link head=NULL;
    int i;
    for(i=0;i<n;i++){
        head=insTail(head,val[i]);
    }
    printlist(head);
    return 0;
}

link newNode(link next,int val){
    link new = malloc(sizeof *new);

    if(new==NULL){
        return NULL;
    }else{
        new->val=val;
        new->next=next;
    }
    return new;
}

link insTail(link head,int val){

    if(head==NULL) return newNode(head,val);

    if(val<head->val) return newNode(head,val);

    link att=head->next;
    link pred=head;

    while(att!=NULL && val>=att->val){
        pred=att;
        att=att->next;
    }

    pred->next= newNode(att,val);

    return head;

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
