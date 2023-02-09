/*
 *Date due liste ordinate,
 * generare una terza lista che contiene gli elementi delle prime due
 * (tranne i duplicati)
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct node *link;

struct node{
    int val;
    link next;
};

link newNode(link next,int val);
link insList(link head,int val);
void printlist(link head);
link createlist(link head1,link head2,link head3);
link insList2(link head,int val);

int main(){
    link head1 = NULL;
    head1=insList(head1,5);
    head1=insList(head1,2);
    head1=insList(head1,1);
    head1=insList(head1,1);
    head1=insList(head1,4);
    head1=insList(head1,4);
    head1=insList(head1,7);
    head1=insList(head1,7);
    head1=insList(head1,6);
    printlist(head1);
    link head2=NULL;
    head2=insList(head2,5);
    head2=insList(head2,2);
    head2=insList(head2,1);
    head2=insList(head2,1);
    head2=insList(head2,1);
    head2=insList(head2,4);
    head2=insList(head2,7);
    head2=insList(head2,7);
    head2=insList(head2,13);
    head2=insList(head2,13);
    head2=insList(head2,1384);
    head2=insList(head2,6);
    link head3=NULL;
    head3=createlist(head1,head2,head3);
    printlist(head3);
    return 0;

}

link newNode(link next,int val){
    link x = malloc(sizeof(*x));
    if(x==NULL) return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}
link insList(link head,int val){

    if(head==NULL){ //inserimento in testa
        return newNode(head,val);
    }else{
        if(val<head->val){
            return newNode(head,val);
        }else{
            link att = head->next;
            link pred = head;
            while(att!=NULL && val>=att->val){
                pred=att;
                att=att->next;
            }
            pred->next= newNode(att,val);
        }
    }
    return head;
}

void printlist(link head){
    link tmp=head;
    printf("\n");
    while(tmp->next!=NULL){
        printf("%d->",tmp->val);
        tmp=tmp->next;
    }
    printf("%d",tmp->val);
}

link createlist(link head1,link head2,link head3){
    link tmp=head1;
    while(tmp!=NULL){
        head3=insList2(head3,tmp->val);
        tmp=tmp->next;
    }
    tmp=head2;
    while(tmp!=NULL){
        head3= insList2(head3,tmp->val);
        tmp=tmp->next;
    }
    return head3;
}

link insList2(link head,int val){

    if(head==NULL){ //inserimento in testa
        return newNode(head,val);
    }else{
        if(val==head->val) return head;
        if(val<head->val){
            return newNode(head,val);
        }else{
            link att = head->next;
            link pred = head;
            while(att!=NULL && val>=att->val){
                pred=att;
                att=att->next;
            }
            if(pred!=NULL && val==pred->val) return head;
            pred->next= newNode(att,val);
        }
    }
    return head;
}
