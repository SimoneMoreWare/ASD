#include <stdlib.h>
#include <stdio.h>

typedef struct node *link;

struct node{
    int val;
    link next;
};

link newNode(link next,int val);
void printList(link head);
link deleteval(link head,int val);

int main(){

    link head=NULL;

    head= newNode(head,7);
    head= newNode(head,10);
    head= newNode(head,11);
    head= newNode(head,6);
    head= newNode(head,4);
    head= newNode(head,3);
    head= newNode(head,4);
    head= newNode(head,1);
    head= newNode(head,4);
    head= newNode(head,67);
    head= newNode(head,4);
    printList(head);
    int val=4;
    head=deleteval(head,val);
    printList(head);
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


void printList(link head){
    printf("\n");
    link tmp=head;
    while(tmp->next!=NULL){
        printf("%d->",tmp->val);
        tmp=tmp->next;
    }
    printf("%d",tmp->val);
}

link deleteval(link head,int val){

    link att=head;
    link pred=NULL;

    while(att!=NULL){
        if(pred==NULL && att->val==val){
            link tmp=att;
            head=head->next;
            att=att->next;
            free(tmp);
        }else{
            if(att->val==val){
                link tmp=att;
                pred->next=att->next;
                att=att->next;
                free(tmp);
            }else{
                pred=att;
                att=att->next;
            }
        }
    }
    return head;
}
