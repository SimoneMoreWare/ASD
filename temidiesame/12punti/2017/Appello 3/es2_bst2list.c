#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list1 {
    char concessionario[100];
    float prezzo;
    struct list1 *next;
} list1_t;

typedef struct list2 {
    char modello[100];
    char concessionario[100];
    float prezzo;
    struct list2 *next;
} list2_t;

typedef struct bst {
    char modello[100];
    list1_t *lista;
    struct bst *left;
    struct bst *right;
} bst_t;

void bst2list(bst_t *bst, list2_t **head, list2_t **tail) {
    if(bst==NULL) return;
    //visita in order, in questo modo posso inserire gli elementi in una lista ordinata
    bst2list(bst->left,head,tail);

    //trovo per ogni modello il prezzo minimo e il consensarrio che vende tale modello a prezzo minimo in modo tale
    //da creare il valore per inserire nella seconda lista

    //l inserimento del nuovo valore avviene in coda, in O(1) in quanto c'è tail
    list1_t *listabst = bst->lista;
    float prezzominimo=listabst->prezzo;
    char rmbconcessionario[100];
    strcpy(rmbconcessionario,listabst->concessionario);
    listabst=listabst->next;
    while(listabst!=NULL){
        if(listabst->prezzo < prezzominimo){ //scorro la lista e trovo la concessionaria a prezzo minimo
            prezzominimo=listabst->prezzo;
            strcpy(rmbconcessionario,listabst->concessionario);
        }
        listabst=listabst->next;
    }
    //creo nuovo nodo per la seconda lista
    list2_t *new = malloc(sizeof(list2_t));
    strcpy(new->modello,bst->modello);//ha come modello la chiave del bst
    strcpy(new->concessionario,rmbconcessionario);
    new->prezzo=prezzominimo;
    new->next=NULL;
    /*
     * Se head è nullo, significa che la lista è vuota. In questo caso, head e tail vengono entrambi impostati su nuovo.
     * Questo significa che la lista ora ha un solo elemento, che è anche la testa e la coda della lista.
Se head non è nullo, significa che la lista ha già almeno un elemento. In questo caso, l'elemento successivo di
     tail viene impostato su nuovo. Inoltre, tail viene impostato su nuovo. Questo significa che tail ora punta
     al nuovo elemento appena inserito, che diventa quindi la coda della list
     */
    if((*head)==NULL){//se la testa è vuota, inserzione in testa, qui testa e coda coincidiono
        (*head)=new;
        (*tail)=new;
    }else{
        (*tail)->next=new;//il successivo alla coda attuale punterà al nuovo nodo
        (*tail)=new;//aggiorno la coda
    }
    bst2list(bst->right,head,tail);
}

int main() {
    bst_t *radice = (bst_t *)malloc(sizeof(bst_t));
    strcpy(radice->modello, "Alfa Romeo");
    radice->lista = (list1_t *)malloc(sizeof(list1_t));
    strcpy(radice->lista->concessionario, "Concessionario 1");
    radice->lista->prezzo = (float) 25000.0;
    radice->lista->next = (list1_t *)malloc(sizeof(list1_t));
    strcpy(radice->lista->next->concessionario, "Concessionario 2");
    radice->lista->next->prezzo = (float)27000.0;
    radice->lista->next->next = NULL;
    radice->left = (bst_t *)malloc(sizeof(bst_t));
    strcpy(radice->left->modello, "Audi");
    radice->left->lista = (list1_t *)malloc(sizeof(list1_t));
    strcpy(radice->left->lista->concessionario, "Concessionario 3");
    radice->left->lista->prezzo = (float)35000.0;
    radice->left->lista->next = NULL;
    radice->left->left = NULL;
    radice->left->right = NULL;
    radice->right = (bst_t *)malloc(sizeof(bst_t));
    strcpy(radice->right->modello, "BMW");
    radice->right->lista = (list1_t *)malloc(sizeof(list1_t));
    strcpy(radice->right->lista->concessionario, "Concessionario 4");
    radice->right->lista->prezzo = (float)32000.0;
    radice->right->lista->next = NULL;
    radice->right->left = NULL;
    radice->right->right = NULL;

    list2_t *head = NULL;
    list2_t *tail = NULL;
    bst2list(radice, &head, &tail);

    list2_t *corrente = head;
    while (corrente != NULL) {
        printf("Modello: %s, Concessionario: %s, Prezzo: %.2f\n", corrente->modello, corrente->concessionario, corrente->prezzo);
        corrente = corrente->next;
    }

    return 0;
}
