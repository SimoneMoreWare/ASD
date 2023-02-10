#include <stdlib.h>
#include <stdio.h>

typedef struct node *link;

struct node{
    int val;
    link next;
};

link newNode(int val,link next);
void printList(link head);
link eliminainposdispari(link head);
int main(){
    link head=NULL;
    head= newNode(6,head);
    head= newNode(7,head);
    head= newNode(8,head);
    head= newNode(9,head);
    head= newNode(20,head);
    head= newNode(3,head);
    head= newNode(14,head);
    head= newNode(141,head);
    head= newNode(71,head);
    head= newNode(52,head);
    head= newNode(15,head);
    head= newNode(41,head);
    head= newNode(12,head);
    printList(head);
    head=eliminainposdispari(head);
    printList(head);
    return 0;
}

link newNode(int val,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL){
        return NULL;
    }else{
        x->val=val;
        x->next=next;
    }
    return x;
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

link eliminainposdispari(link head){
    link att,pred,tmp;

    att=head;
    pred=NULL;
    int count=0;

    while(att!=NULL){
        if(count%2!=0){
            tmp=att;
            pred->next=att->next;
            att=att->next;
            free(tmp);
        }else{
            pred=att;
            att=att->next;
        }
        count++;
    }
    return head;


}
