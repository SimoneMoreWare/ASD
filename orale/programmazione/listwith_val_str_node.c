/*
 * Definire una lista in grado di contenere sia un intero che una stringa
 * (a seconda che si chiami l'una o l'altra funzione di inserzione)
 * di tenere traccia per ogni nodo se quel nodo h tenendo poi conto del tipo di dato effettivamente
 * inserito mediante un flag "type" contenente 0 per gli interi e 1 per le stringhe)
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

struct node{
    int type;
    int val;
    char str[100];
    link next;
};

link newval(link next,int val);
link newstr(link next,char *strval);
link wrapper(link head,int type);
void printList(link head);
int main(){
    link head=NULL;
    head= wrapper(head,0);
    head= wrapper(head,0);
    head= wrapper(head,1);
    head= wrapper(head,1);
    head= wrapper(head,1);
    head= wrapper(head,0);
    head= wrapper(head,1);
    head= wrapper(head,0);
    head= wrapper(head,1);

    printList(head);
    return 0;
}

link wrapper(link head,int type){

    if(type==0){
        int val;
        printf("Inserisci valore:");
        scanf("%d",&val);
        printf("\n");
        return newval(head,val);
    }else{
        char strval[100];
        printf("Inserisci stringa:");
        scanf("%s",strval);
        printf("\n");
        return newstr(head,strval);
    }

    //return head;

}

link newval(link next,int val){
    link new = malloc(sizeof *new);
    if(new==NULL){
        return NULL;
    }else{
        new->val=val;
        strcpy(new->str,"");
        new->type=0;
        new->next=next;
    }
    return new;
}

link newstr(link next,char *strval){
    link new = malloc(sizeof *new);
    if(new==NULL){
        return NULL;
    }else{
        new->val=-1;
        strcpy(new->str,strval);
        new->type=1;
        new->next=next;
    }
    return new;
}

void printList(link head){
    link tmp=head;

    while(tmp->next!=NULL){
        if(tmp->type==0) printf("%d->",tmp->val);
        else printf("%s->",tmp->str);
        tmp=tmp->next;
    }
    if(tmp->type==0) printf("%d",tmp->val);
    else printf("%s",tmp->str);
}
