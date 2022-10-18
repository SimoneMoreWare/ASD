#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;//next è un puntatore a una
    // variabile struct node, quello a cui punta altro
    //non è che una struttura di questo tipo,
    //che avra un val e un next
    //richiama se stesso, si va in fila, si collegano tanti
    //piccoli nodi tra loro
};


//inserimento, passando per riferimento il puntatore head
void list_insert(struct node** head, int new_data);
//stampa, passo "copia", avrà l indirizzo
void list_display(struct node *p);
//ricerca, è possibile anche passarlo non in "riferimento"
int list_search(struct node* corrente, int ricercato);
//cancellazione
void list_delate(struct node** head,int key);

int main(){
    struct node* head=NULL;
    int nodoCercato,nodoCancellato;
    int c=4;
    int f=5;
    int *p;
    p=&c;
    printf("%p",p+4);
    printf("%d ",c/2+c%2);
    printf("%d ",f/2+f%2);

    list_insert(&head,53);
    list_insert(&head,42);
    list_insert(&head,69);

    list_display(head);
    list_insert(&head,12);
    list_display(head);

    nodoCercato=86;
    if (list_search(head,nodoCercato)) printf("%d nodo trovato",nodoCercato);
    else printf("Non ho trovato %d",nodoCercato);

    printf("\n");
    nodoCercato=69;
    if (list_search(head,nodoCercato)) printf("%d nodo trovato",nodoCercato);
    else printf("Non ho trovato %d",nodoCercato);

    list_delate(&head,69);
    list_display(head);

    return 0;
}

//inserimento, passando per riferimento il puntatore head
void list_insert(struct node** head, int new_data){
    //creo nodo di appoggio di tipo puntatore
    struct node* nuovo = (struct node*) malloc(sizeof(struct node));

    //malloc non andata a buon fine
    if(nuovo==NULL){
        printf("Errore nell'allocazione della memoria");
        exit(0);
    }

    //ho un puntatore temporaneo nuovo, uscito dalla funzione viene liberato
    nuovo->data=new_data;
    nuovo->next=(*head);//uguale alla vecchia testa

    (*head)=nuovo;//la vecchia testa sarà il next
}

void list_display(struct node *p){
    printf("\n");

    while(p!=NULL){
        printf("%d ",p->data);
        printf("%p\n ",p->next);
        p=p->next;
    }
}

int list_search(struct node* corrente, int ricercato){
    //struct node* corrente = *head;

    while(corrente!=NULL){
        if(corrente->data==ricercato) return 1;
        corrente=corrente->next;
    }
    return 0;
}

//modificare passa con &, cancello nodo con quella key come dato
//non basta fare free di quel nodo ma
//modificare il next del nodo precedente al successivo del successivo
void list_delate(struct node** head,int key){
    struct node *tmp=*head;
    struct node *prev=NULL;

    //contollo se sto nella testa o la lista è vuota
    if(tmp!=NULL && tmp->data == key){
        *head=tmp->next;//la testa diventa il successivo, il secondo
        free(tmp);//dealloco la parte di memoria di quel nodo
        return;
    }

    //cerco il nodo e tengo traccia del precedente
    while(tmp!=NULL && tmp->data!=key){//se non finisco tmp
        prev=tmp;//prev procede di un nodo risèetto a tmp
        tmp=tmp->next;//vado al nodo sussesivo
    }

    if(tmp==NULL) return; //non ho trovato nulla

    //se ho trovato la key
    //
    prev->next=tmp->next;//trovato quello dal eliminare
    free(tmp);
}
