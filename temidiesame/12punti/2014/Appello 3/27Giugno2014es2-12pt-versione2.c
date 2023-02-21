#include <stdio.h>
#include <stdlib.h>

#define TESTA 0
#define CODA 1
#define TESTACODA 0
#define CODATESTA 1
typedef struct node_t {
	struct node_t* precedente;
	struct node_t* prossimo;
	int chiave;
} node_t;

typedef struct node_t* LINK;

typedef struct list_t {
	LINK testa;
	LINK coda;
} list_t;

void listInit(list_t* list);
void list_insert(list_t* list, int chiave, int estremo);
void list_display(list_t* list, int modo);
void display_alt(list_t* list);

int main(int argc, char **argv)
{
	list_t list;
	
	printf("Programma avviato.\n");
	printf("Creazione lista...\n");
	listInit(&list);
	printf("Lista creata.\n");
	printf("Inserisco i numeri 1 : 10, in modo alternato.\n");
	
	list_insert(&list, 1, TESTA);
	list_insert(&list, 2, CODA);
	list_insert(&list, 3, TESTA);
	list_insert(&list, 4, CODA);
	list_insert(&list, 5, TESTA);
	list_insert(&list, 6, CODA);
	list_insert(&list, 7, TESTA);
	list_insert(&list, 8, CODA);
	list_insert(&list, 9, TESTA);
	list_insert(&list, 10, CODA);
	
	printf("Inserimento completato.\n");
	
	printf("\nVisualizzazione Testa -> Coda: "); list_display(&list, TESTACODA);
	printf("\n\nVisualizzazione Coda -> Testa: "); list_display(&list, CODATESTA);	

	printf("\n\nEsecuzione terminata.\n");
	
	return 420;
}


LINK nodo(LINK precedente, int chiave, LINK prossimo){
	LINK nodo_r = malloc(sizeof(node_t));
	nodo_r->precedente = precedente;
	nodo_r->chiave = chiave;
	nodo_r->prossimo = prossimo;
	return nodo_r;
}

void listInit(list_t* list){
	list->testa = nodo(NULL, 420, NULL);
	list->coda = nodo(NULL, -420, NULL);
	list->testa->prossimo = list->coda;
	list->coda->precedente = list->testa;
}

void list_insert(list_t* list, int chiave, int estremo){
	LINK nuovoElemento, vecchioElemento;
	if (estremo == TESTA){
		vecchioElemento = list->testa->prossimo;
		nuovoElemento = nodo(list->testa, chiave, vecchioElemento);
		vecchioElemento->precedente = nuovoElemento;
		list->testa->prossimo = nuovoElemento;
		return;
	}
	vecchioElemento = list->coda->precedente;
	nuovoElemento = nodo(vecchioElemento, chiave, list->coda);
	vecchioElemento->prossimo = nuovoElemento;
	list->coda->precedente = nuovoElemento;
}

void list_displayR(LINK nodo, LINK sentinella, int modo){
	if (nodo == sentinella) return;
	printf("%d ", nodo->chiave);
	if (modo == TESTACODA) list_displayR(nodo->prossimo, sentinella, modo);
	else 				   list_displayR(nodo->precedente, sentinella, modo);

}

void list_display(list_t* list, int modo){
	if(modo == TESTACODA) list_displayR(list->testa->prossimo, list->coda, TESTACODA);
	else list_displayR(list->coda->precedente, list->testa, CODATESTA);
}
