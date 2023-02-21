#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	/*
	 * char* nome;
	 * char* cognome;
	 * int voto;
	 * Sto tema è proprio noioso, ci siamo capiti;
	 */
	 char carattere;
	 struct node_t* figlio;
	 struct node_t* fratello;
} node_t;

node_t* albero();
node_t* nodo(char carattere, node_t* figlio, node_t* fratello);
void visita(node_t* albero);

int main(int argc, char **argv)
{
	printf("Inizio esecuzione.\n");
	printf("Genero albero LCRS...\n");
	node_t* famiglia = albero();
	printf("Generazione albero terminata.\n");
	printf("Visita: ");
	visita(famiglia);
	printf("\nTermino esecuzione...");
	return 1;
}

node_t* albero(){
	node_t* g = nodo('G', NULL, NULL);
	node_t* f = nodo('F', NULL, g);
	node_t* j = nodo('J', NULL, NULL);
	node_t* i = nodo('I', NULL, j);
	node_t* h = nodo('H', NULL, i);
	node_t* e = nodo('E', h, NULL);
	node_t* d = nodo('D', f, NULL);
	node_t* c = nodo('C', NULL, d);
	node_t* b = nodo('B', e, c);
	node_t* a = nodo('A', b, NULL);
	
	return a; //Ci è voluto di più a scrivere sta roba
}

node_t* nodo(char carattere, node_t* figlio, node_t* fratello){
	node_t* node = malloc(sizeof(node_t));
	node->carattere = carattere;
	node->figlio = figlio;
	node->fratello = fratello;
	return node;
}

void visita(node_t* albero){
	if (albero == NULL) return;
	visita(albero->figlio);
	printf("%c ", albero->carattere);
	visita(albero->fratello);
	//L'ordine probabilmente è preferenziale
}