#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSZ 30+1

typedef struct list1 {
	char concessionario[STRSZ];
	float prezzo;
	struct list1 *next;
} list1_t;

typedef list1_t list2_t;

typedef struct bst_node {
	char modello[STRSZ];
	list1_t* listaConcessionari;
	struct bst_node *left;
	struct bst_node *right;
} bst_t;

bst_t* BSTNEWINSERT(bst_t * bst, char modello[STRSZ], char concessionario[STRSZ], float prezzo);
list1_t* LISTINSERT(list1_t* next, char concessionario[STRSZ], float prezzo);
bst_t* concessionario();
void visit(bst_t * bst);
void listVisit(list1_t *list);

void bst2list(bst_t* bst, list2_t **head, list2_t **tail);

int main(int argc, char **argv)
{
	bst_t* automobili;
	list1_t *head, *tail;
	automobili = concessionario();
	bst2list(automobili, &head, &tail);
	listVisit(head);
	
	return 0;
}

bst_t* BSTNEWINSERT(bst_t * bst, char modello[STRSZ], char concessionario[STRSZ], float prezzo){
	int n;
	bst_t* node;
	if ( bst == NULL ){
		node = malloc(sizeof(bst_t));
		strcpy(node->modello, modello);
		node->left = NULL;
		node->right = NULL;
		node->listaConcessionari = LISTINSERT(NULL, concessionario, prezzo);
		return node;
	}
	
	n = strcmp(bst->modello, modello);
	
	if (n == 0){
		bst->listaConcessionari = LISTINSERT(bst->listaConcessionari, concessionario, prezzo);
		return bst;;
	}
	
	if (n < 0){
		bst->right = BSTNEWINSERT(bst->right, modello, concessionario, prezzo);
		return bst;
	}
	
	bst->left = BSTNEWINSERT(bst->left, modello, concessionario, prezzo);
	return bst;
}
list1_t* LISTINSERT(list1_t *next, char concessionario[STRSZ], float prezzo){
	list1_t* nodo = malloc(sizeof(list1_t));
	strcpy(nodo->concessionario, concessionario);
	nodo->prezzo = prezzo;
	nodo->next = next;
	return nodo;
}

bst_t* concessionario(){
	bst_t* bst = NULL;
	bst = BSTNEWINSERT(bst, "Fiat Punto", "Carmiano", 10000.50);
	bst = BSTNEWINSERT(bst, "Fiat Punto", "Novoli", 12000.50);
	bst = BSTNEWINSERT(bst, "Fiat Punto", "Lecce", 11500.50);
	
	bst = BSTNEWINSERT(bst, "Fiat Panda", "Novoli", 5000.30);
	bst = BSTNEWINSERT(bst, "Fiat Panda", "Lecce", 7000.80);
	bst = BSTNEWINSERT(bst, "Fiat Panda", "Carmiano", 6550.50);
	
	bst = BSTNEWINSERT(bst, "Fiat Bravo", "Lecce", 13500.50);
	bst = BSTNEWINSERT(bst, "Fiat Bravo", "Novoli", 15000.70);
	bst = BSTNEWINSERT(bst, "Fiat Bravo", "Carmiano", 18000.50);
	
	return bst;
}

void visit(bst_t * bst){
	if (bst == NULL) return;
	visit(bst->left);
	printf("%s ", bst->modello);
	visit(bst->right);
}


void listVisit(list1_t *list){
	if (list == NULL) return;
	printf("%s %.2f\n", list->concessionario, list->prezzo);
	listVisit(list->next);
}


void bst2listR(bst_t* bst, list2_t **tail){
	if (bst == NULL) return;
	list1_t* node, *bestNode;
	bst2listR(bst->left, tail);
	bestNode = bst->listaConcessionari;
	for(node = bst->listaConcessionari; node != NULL; node = node->next)
		if (node->prezzo < bestNode->prezzo) bestNode = node;
	(*tail) = LISTINSERT( (*tail), bestNode->concessionario, bestNode->prezzo);
	bst2listR(bst->right, tail);
}

void bst2list(bst_t* bst, list2_t **head, list2_t **tail){
	*tail = NULL;
	bst2listR(bst, tail);
	*head = *tail;
}