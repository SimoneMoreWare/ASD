#include <stdio.h>
#include <stdlib.h>



struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};


struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
void purge(struct Node *head, int div);
int main() {
    struct Node *head = NULL;
    struct Node *tail = NULL;

    for (int i = 9; i >= 0; i--) {
        struct Node *newNode = createNode(i);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Stampa i valori della lista
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
    purge(head,3);
    return 0;
}

void purge(struct Node *head, int div){

    struct Node * att = head;
    struct Node * pred = NULL;
    struct Node * tmp;
    while(att!=NULL){
        if(att->data % div != 0){
            tmp=att;
            pred->next=att->next;
            att=att->next;
            free(tmp);
        }else{
            pred=att;
            att=att->next;
        }
    }
    tmp=head;
    while (tmp != NULL) {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
}
