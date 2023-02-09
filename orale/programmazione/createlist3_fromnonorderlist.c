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
link createlist(link head1,link head2,link head3);
link insOrdcustom(link head,int val);

int main(){
    link head1=NULL;
    head1= newNode(5,head1);
    head1= newNode(3,head1);
    head1= newNode(6,head1);
    head1= newNode(4,head1);
    head1= newNode(2,head1);
    head1= newNode(1,head1);
    printlist(head1);
    link head2=NULL;
    head2=newNode(4,head2);
    head2=newNode(6,head2);
    head2=newNode(9,head2);
    head2=newNode(1,head2);
    head2=newNode(74,head2);
    head2=newNode(10,head2);
    link head3=NULL;
    head3=createlist(head1,head2,head3);
    printlist(head3);
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

link createlist(link head1,link head2,link head3){
    link tmp;
    tmp = head1;
    while(tmp!=NULL){
        head3=insOrdcustom(head3,tmp->val);
        tmp=tmp->next;
    }
    tmp=head2;
    while(tmp!=NULL){
        head3= insOrdcustom(head3,tmp->val);
        tmp=tmp->next;
    }
    return head3;
}

link insOrdcustom(link head,int val){

    if(head==NULL){
        return newNode(val,head);
    }else{
        if(val==head->val) return head;
        if(val<head->val) return newNode(val,head);
        link att=head->next;
        link pred=head;
        while(att!=NULL && val>=att->val){
            pred=att;
            att=att->next;
        }
        if(pred->val==val) return head;
        pred->next=newNode(val,att);
    }
    return head;
}
