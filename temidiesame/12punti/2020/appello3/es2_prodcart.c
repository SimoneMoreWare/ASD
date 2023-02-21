#include <stdio.h>
#include <stdlib.h>

typedef struct list *LIST;

typedef struct{
    int x;
    int y;
}coppia;

typedef struct node *link;

struct node{
    coppia val;
    link next;
};

struct list{
    link head;
};

LIST prodCart(int v1[3],int d1,int v2[4],int d2);
link inserimentoinlistaordinata(link head,int x,int y);

int main(){
    int v1[]={1,2,3};
    int v2[]={3,4,5,6};
    int d1=3;
    int d2=4;
    LIST l;
    l=prodCart(v1,d1,v2,d2);
    link tmp=l->head;
    while(tmp!=NULL){
        printf("(%d,%d),",tmp->val.x,tmp->val.y);
        tmp=tmp->next;
    }
}

LIST prodCart(int v1[3],int d1,int v2[4],int d2){
    LIST l = malloc(sizeof(LIST));
    l->head=NULL;
    int i,j;
    for(i=0;i<d1;i++){
        for(j=0;j<d2;j++){
            l->head=inserimentoinlistaordinata(l->head,v1[i],v2[j]);
        }
    }
    return l;
}

link inserimentoinlistaordinata(link head,int x,int y) {
    link new = malloc(sizeof(*new));
    link att,pred;
    int sommaparziale;
    //testa vuota,inserimento in testa;
    if(head==NULL){
        new->next=NULL;
        new->val.x=x;
        new->val.y=y;
        return new;
    }else{
        sommaparziale = x+y;
        //se l'elemento che voglio inserire è minore del primo valore (ossia la testa), devo effettuare l'inserimento in testa
        if(sommaparziale < (head->val.x + head->val.y)){
            new->next=head;
            new->val.x=x;
            new->val.y=y;
            return new;
        }else{
            att=head->next;
            pred=head;
            while(att!=NULL && sommaparziale>=(att->val.x + att->val.y)){
                pred=att;
                att=att->next;
            }
            pred->next = new;
            new->next=att;
            new->val.x=x;
            new->val.y=y;
        }
    }
    return head;
}
