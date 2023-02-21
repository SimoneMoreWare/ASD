#include <stdio.h>
#include <stdlib.h>


typedef struct node *link;
struct node
{
    int val;
    link next;
};

//------------------------
link newnode();
int aggiungi(link *head);
link inserimentoinlistaordinata(link head,int datanew);
int f(link head);
int main()
{
    int n;
    link head=newnode();

    head->val=4;
    head->next=newnode();
    head->next->val=7;
    head->next->next=newnode();
    head->next->next->val=10;

    n=f(head);

    printf("\n\n%d nodi aggiunti\n",n);


    return 0;
}

link newnode()
{
    link x=malloc(sizeof(*x));
    x->next=NULL;
    x->val=-1;
    return x;
}

int f(link head){
    int n;
    n = aggiungi(&head);
    link tmp = head;
    while(tmp!=NULL){
        printf("%d ",tmp->val);
        tmp=tmp->next;
    }
    return n;
}

int aggiungi(link *head){

    link tmp;
    int attuale;
    int successivo;
    int iterazioni;
    int i;
    int n=0;

    tmp = (*head);

    while(tmp->next!=NULL){

        attuale = tmp->val;
        successivo = tmp->next->val;
        iterazioni = successivo-attuale-1;

        for(i=1;i<iterazioni+1;i++){
            (*head) = inserimentoinlistaordinata((*head),attuale+i);
            n++;
        }
        tmp=tmp->next;
    }
    return n;
}

link inserimentoinlistaordinata(link head,int datanew){
    link x,p;
    link new = malloc(sizeof(link));
    new->val=datanew;
    new->next=NULL;

    // non serve if(head==NULL)

    x=head->next;
    p=head;
    while(x!=NULL && datanew>=x->val){
        p=x;
        x=x->next;
    }

    p->next = new;
    new->next = x;

    return head;
}
