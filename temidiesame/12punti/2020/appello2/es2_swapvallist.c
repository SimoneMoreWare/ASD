#include <stdio.h>
#include <stdlib.h>

typedef struct Node *link;
struct Node {
    int data;
    link next;
};


void insert(link *head,int data) {
    link temp = malloc(sizeof(*temp));
    temp->data = data;
    temp->next = (*head);
    (*head) = temp;
}

void printList(link head) {
    link temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void swap(link *head, int k){

    int lunghezza_lista=0;
    link tmp = (*head);

    while(tmp!=NULL){
        lunghezza_lista++;
        tmp=tmp->next;
    }

    int distcoda_fromhead = lunghezza_lista-k-1;

    int cnt=0;
    link att = (*head);
    link nodo1;
    link nodo2;
    int val1;
    int val2;
    int flag=0;
    while(att!=NULL && flag!=2){
        if(cnt==k){
            val1=att->data;
            nodo1=att;
            flag++;
        }
        if(cnt==distcoda_fromhead){
            val2=att->data;
            nodo2=att;
            flag++;
        }
        att=att->next;
        cnt++;
    }
    nodo1->data=val2;
    nodo2->data=val1;
}

int main() {
    link head = NULL;

    insert(&head,70);
    insert(&head,60);
    insert(&head,50);
    insert(&head,40);
    insert(&head,30);
    insert(&head,20);
    insert(&head,10);
    printList(head);
    swap(&head,2);
    printList(head);

    return 0;
}
