/*
 * Data una matrice e noti numero di righe e colonne,
 * creare un vettore di liste che copi il contenuto della matrice eliminando gli zeri
 * e che salvi in ogni nodo sia il valore sia il suo indice di colonna
 */

#include <stdlib.h>
#include <stdio.h>

typedef struct node *link;

struct node{
    int val;
    link next;
};

link newNode(int val,link next){
    link x = malloc(sizeof(*x));
    if(x==NULL) return NULL;
    else{
        x->next=next;
        x->val=val;
    }
    return x;
}

link inserimentoincoda(int val,link head){
    link tmp;
    if(head==NULL){
        return newNode(val,head);
    }else{
        tmp=head;
        while(tmp->next!=NULL) tmp=tmp->next;
        tmp->next=newNode(val,NULL);
    }
    return head;
}

int main(){
    int matrix[5][5]={
            {0,1,2,0,0},
            {0,0,0,0,0},
            {4,2,3,1,0},
            {1,151,411,21,1},
            {1,0,0,0,0}
    };
    int r=5;
    int c=5;
    link *vet = (link*) malloc(r*sizeof(link));
    int i,j;
    for(i=0;i<r;i++) vet[i]=NULL;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            if(matrix[i][j]!=0){
                vet[i]=inserimentoincoda(matrix[i][j],vet[i]);
            }
        }
    }
    link tmp;
    for(i=0;i<r;i++){
        tmp=vet[i];
        while(tmp!=NULL){
            printf("%d ",tmp->val);
            tmp=tmp->next;
        }
        printf("\n");
    }
}

