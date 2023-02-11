#include <stdlib.h>
#include <stdio.h>

typedef struct node *link;

struct node{
    int val;
    link head;
    link next;
};

link newNode(link next,int val);
link insOrd(link head,int val);
void printList(link head);
void createvalueinlistinlist(int key,int valsec,link head);

int main(){

    link head=NULL;

    head=insOrd(head,4);
    head=insOrd(head,2);
    head=insOrd(head,1);
    head=insOrd(head,1);
    head=insOrd(head,4);
    head=insOrd(head,0);
    head=insOrd(head,10);
    printList(head);
    int key=4;
    int valsec=56;
    createvalueinlistinlist(key,valsec,head);
    printList(head);
    return 0;
}

link newNode(link next,int val){
    link new = malloc(sizeof *new);
    if(new==NULL){
        return NULL;
    }else{
        new->val=val;
        new->head=NULL;
        new->next=next;
    }
    return new;
}

link insOrd(link head,int val){

    if(head==NULL) return newNode(NULL,val);
    else{
        if(val<head->val) return newNode(head,val);
        else{
            link att=head->next;
            link pred=head;
            while(att!=NULL && val>=att->val){
                pred=att;
                att=att->next;
            }
            pred->next= newNode(att,val);
        }
    }
    return head;

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

void createvalueinlistinlist(int key,int valsec,link head){
    link tmp=head;
    while(tmp!=NULL){
        if(tmp->val == key){
            link x = malloc(sizeof *x);
            x->val=valsec;
            x->next=NULL;
            tmp->head=x;
            return;
        }
        tmp=tmp->next;
    }
    printf("Chiave non presente\n");
}
