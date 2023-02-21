#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct persona {
    char *nome;
    char *cognome;
}Persona;

typedef struct listNode *link;

struct listNode {
    Persona p;
    link next;
};

typedef struct l_t{
    link head;
}lista_t;

int inserisciInOrdine(lista_t *lista, char *cognome, char *nome);
void stampaLista(lista_t *lista);

int main(){
    char cognome[20];
    char nome[20];
    int result, i;
    lista_t *lista;

    lista = malloc(sizeof(*lista));
    lista->head = NULL;

    for(i=0; i<5; i++){
        printf("Inserisci cognome: ");
        scanf("%s", cognome);
        printf("Inserisci nome: ");
        scanf("%s", nome);

        result = inserisciInOrdine(lista, cognome, nome);
        printf("%d\n", result);

    }

    stampaLista(lista);

    return 0;
}

int inserisciInOrdine(lista_t *lista, char *cognome, char *nome){
    link x,t,p;
    x=malloc(sizeof(*x));

    x->p.cognome = strdup(cognome);
    x->p.nome = strdup(nome);
    x->next = NULL;

    t = lista->head;
    p = t;

    while(t!=NULL && (strcmp(t->p.cognome,cognome)<0 || (strcmp(t->p.cognome,cognome)==0 && strcmp(t->p.nome,nome)<0))){
        p = t;
        t = t->next;
    }

    if(t==lista->head){
        printf("t = head");
        x->next = lista->head;
        lista->head = x;
        return 1;
    }

    printf("else");

    p->next = x;
    if(t!=NULL)
        x->next = t;

    return 1;
}

void stampaLista(lista_t *lista){
    link t;

    for(t=lista->head; t!=NULL; t=t->next){
        printf("%s %s \n", t->p.cognome, t->p.nome);
    }
    return;
}
