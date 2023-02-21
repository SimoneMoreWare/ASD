#include <stdio.h>
#include <stdlib.h>

typedef struct node nodo_t;

struct node{
    int chiave;
    nodo_t *previous;
    nodo_t *next;
};

typedef struct list {
    nodo_t *head;
    nodo_t *tail;
}list_t;

void list_insert (list_t *l, int chiave, int estremo);
void list_display (list_t *l, int modo);

int main()
{
    list_t *l;

    l = malloc(sizeof(*l));
    l->head = NULL;
    l->tail = NULL;

    list_insert(l,1,0);
    list_insert(l,2,1);
    list_insert(l,3,1);
    list_insert(l,0,0);
    list_insert(l,4,1);

    list_display(l,0);
    list_display(l,1);

    return 0;
}

void list_insert (list_t *l, int chiave, int estremo){
    nodo_t *x;
    x = malloc(sizeof(*x));

    x->chiave = chiave;
    x->next = NULL;
    x->previous = NULL;

    if(estremo == 0){
        if(l->head == NULL){
            l->head = x;
            l->tail = x;
        } else {
            x->next = l->head;
            l->head->previous = x;
            l->head = x;
        }
    } else if(estremo == 1){
        if(l->tail == NULL){
            l->head = x;
            l->tail = x;
        } else {
            l->tail->next = x;
            x->previous = l->tail;
            l->tail = x;
        }
    } else {
        printf("Errore!");
    }
    return;
}

void list_display (list_t *l, int modo){
    nodo_t *x;

    if(modo == 0){
        printf("Reading from head to tail\n");
        for(x = l->head; x != NULL; x = x->next)
            printf("%d ", x->chiave);
        printf("\n");
    } else if(modo == 1) {
        printf("Reading from tail to head\n");
        for(x = l->tail; x != NULL; x = x->previous)
            printf("%d ", x->chiave);
        printf("\n");
    } else {
        printf("Errore!");
    }
    return;
}
