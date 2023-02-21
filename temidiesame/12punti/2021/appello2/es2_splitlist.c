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

LIST* split(LIST l, int *n);
link inserimentoincoda(int val,link head);

int main() {
    LIST l = malloc(sizeof(struct list)); //devo allocare la memoria per lista, 
    /*
    Devi allocare memoria per la lista perché è un puntatore a una struttura. Se non allocheresti la memoria, l'indirizzo di memoria a cui punta la variabile sarebbe sconosciuto e non potresti accedere alla struttura. Allocare memoria significa richiedere un blocco di memoria per una struttura in modo che l'indirizzo di memoria a cui punta la variabile sia noto e possa essere utilizzato per accedere alla struttura.
    */
    l->head=NULL;
    NODE *node = malloc(sizeof(NODE));
    node->data = 5;
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

    int n=0;
    LIST *lists = split(l, &n);

    printf("Original list: ");
    link p = l->head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");

    printf("Split into %d lists:\n", n);
    for (int i = 0; i < n; i++) {
        printf("List %d: ", i + 1);
        p = lists[i]->head;
        while (p != NULL) {
            printf("%d ", p->data);
            p = p->next;
        }
        printf("\n");
    }

    return 0;
}

LIST* split(LIST l, int *n){
    LIST *res;
    int i;
    link tmp = l->head; //vedo la dimensione della lista da creare
    while(tmp->next!=NULL){
        if(((tmp->data)%2==0) && ((tmp->next->data)%2!=0)) (*n)++; //se valore attuale è pari, e quello successivo è dispari, allora incremento dimensione
        if(((tmp->data)%2!=0) && ((tmp->next->data)%2==0)) (*n)++; //se valore atutale è dispari, e quello successivo è pari, allora incremento dimensione
        tmp=tmp->next; //scorro sulla lista
    }
    (*n)++;//arrivato alla fine devo ricordarmi di incrementare, perchè se non lo faccio perdo ultima sequenza
    (res) = malloc((*n)*sizeof(res)); //inizializzo array di liste
    for(i=0;i<(*n);i++){//per ogni cella devo creare la la lista
        res[i]=malloc(sizeof(struct list));
        res[i]->head=NULL; //ricordarsi di inizallizare a null la testa, per ogni cella
    }

    tmp = l->head; //scorro nuovamente sulla lista originale
    int pos=0; //variabile per tenere traccia della cella in cui inserire i valori della lista  
    while(tmp->next!=NULL){ 
        if( (((tmp->data)%2==0) && ((tmp->next->data)%2==0)) || (((tmp->data)%2!=0) && ((tmp->next->data)%2!=0))){ //se il valore attuale e il valore successivo sono entrambi pari (o dispari), inserisco in coda nella lista in posizione pos, il valore attuale della lista che sto scorrendo
            res[pos]->head= inserimentoincoda(tmp->data,res[pos]->head); //inserisco in coda il valore attuale della lista che sto scorrendo in posizone pos
        }else{
            res[pos]->head = inserimentoincoda(tmp->data,res[pos]->head); //inserisco l ultimo valore nella lista in posizione pos
            pos++; //la lista in posizone pos è stata completa, quindi si passa alla lista successiva
        }
        tmp=tmp->next;
    }
    //if(pos!=((*n)-1))
    res[pos]->head = inserimentoincoda(tmp->data,res[pos]->head); //ricordiamoci sempre dell ultimo valore da inserire nella posizoone pos
    //else res[pos]->head = inserimentoincoda(tmp->data,res[pos]->head);

    return res;

 }

link inserimentoincoda(int val,link head){

    link x = malloc(sizeof *x);
    if(head==NULL){
        x->data=val;
        x->next=NULL;
        return x; //ricordati di ritornare x, e non head, perchè altrimenti ritorno null sempre
    }else{
        link tmp=head;
        while(tmp->next!=NULL) tmp=tmp->next;
        tmp->next=x;
        x->data=val;
        x->next=NULL;
    }
    return head;
}
