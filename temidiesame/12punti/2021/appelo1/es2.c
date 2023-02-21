#include <stdio.h>
#include <stdlib.h>

typedef struct node *link;

typedef struct node {
    int data;
    link next;
} NODE;

typedef struct list *LIST;

struct list{
    link head;
};

void f(LIST l, int *v, int n);
int cmpfunc (const void * a, const void * b);
link fR(link head,int *v,int n);
int binarySearchRecursive(int arr[], int left, int right, int x);

int main() {
    LIST l = malloc(sizeof(struct list)); //devo allocare la memoria per lista, 
    /*
    Devi allocare memoria per la lista perché è un puntatore a una struttura. Se non allocheresti la memoria, l'indirizzo di memoria a cui punta la variabile sarebbe sconosciuto e non potresti accedere alla struttura. Allocare memoria significa richiedere un blocco di memoria per una struttura in modo che l'indirizzo di memoria a cui punta la variabile sia noto e possa essere utilizzato per accedere alla struttura.
    */
    l->head=NULL;
    NODE *node = malloc(sizeof(NODE));
    node->data = 4;
    node->next = NULL;
    l->head = node;

    node = malloc(sizeof(NODE));
    node->data = 1;
    node->next = l->head;
    l->head = node;

    node = malloc(sizeof(NODE));
    node->data = 3;
    node->next = l->head;
    l->head = node;

    node = malloc(sizeof(NODE));
    node->data = 6;
    node->next = l->head;
    l->head = node;

    node = malloc(sizeof(NODE));
    node->data = 10;
    node->next = l->head;
    l->head = node;

    node = malloc(sizeof(NODE));
    node->data = 3;
    node->next = l->head;
    l->head = node;


    printf("Original list: ");
    link p = l->head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");

    int v[3]={1,2,3};
    int n=3;
    f(l,v,n);
    p = l->head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int binarySearchRecursive(int arr[], int left, int right, int x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] > x)
            return binarySearchRecursive(arr, left, mid - 1, x);

        return binarySearchRecursive(arr, mid + 1, right, x);
    }

    return -1;
}

void f(LIST l, int *v, int n){

    qsort(v,n,sizeof(int),cmpfunc);
    l->head=fR(l->head,v,n);
}

/*
 *
 * Questo codice è una funzione che riceve tre parametri:
 * una lista (l), un vettore di interi (v), e un intero (n).
 * La funzione implementa un algoritmo che rimuove i nodi dalla lista
 * che non contengono valori presenti nel vettore v.
 */

link fR(link head,int *v,int n){

    link tmp;
    link att=head;
    link prev=NULL;


/*
 * La funzione f effettua una scansione della lista e cancella tutti i
 * nodi che non contengono un valore presente nel vettore v.
 * La funzione contains viene utilizzata per verificare se un
 * valore x è presente nel vettore v. Durante la scansione,
 * si utilizza un puntatore prev per tenere traccia del
 * nodo precedente a quello corrente, in modo da poter
 * effettuare correttamente la rimozione del nodo corrente.




 */

    while(att!=NULL){
        if(binarySearchRecursive(v,0,n,att->data)==-1){//controllo se il valore del nodo corrente non è presente nel vettore
            /*
             * if (prev == NULL): Controlla se il puntatore prev è nullo.
             * Se questa condizione è vera, significa che il nodo
             * corrente è la testa della lista.
             * non basta farlo una volta, tipo all inizio,
             * ma bisogna farlo sempre, magari devo sempre eliminare
             * il nodo in testa
             */
            if(prev==NULL){
                tmp=att;
                head=att->next;//assegna la testa al prossima nodo
                free(tmp);//libero la memoria allocata per il nodo corrente
                att=head; //assegna al puntatore att la nuova testa della lista
            }else{
                tmp=att;
                prev->next=att->next;//prev->next = curr->next: Rimuove il nodo corrente dalla lista impostando il puntatore next del nodo precedente alla posizione successiva del nodo corrente.
                att=att->next;
                free(tmp);//libea la memoria per il nodo corrente
            }
        }else{
            prev=att;
            att=att->next;
        }
    }
    return head;
}
