#include <stdio.h>
#include <stdlib.h>

#define RIGHE 10
#define COLONNE 5

typedef struct node_t {
	int colonna;
	float valore;
	struct node_t* prossimaColonna;
} node_t;

typedef struct matr_t {
	int righe;
	int colonne;
	node_t** righe_liste;
	node_t* sentinella;
} matr_t;

void init(matr_t* matrice, int righe, int colonne);
void inserisci(matr_t* matrice, int riga, int colonna, float value); //MATRwrite è un brutto nome
void stampa(matr_t* matrice);

int main(int narg, char** args){
	
	matr_t matrice;
	int riga = 1, colonna = 1;
	float valore = 1;
	printf("Inizio esecuzione.\n");
	
	init(&matrice, RIGHE, COLONNE);
	
	printf("Inserire una posizione non valida per terminare.\n");
	
	while(riga > -1 && colonna > -1){	
		printf("Inserire la riga: ");
		scanf("%d", &riga); fflush(stdin);
		if (riga > -1 && riga < matrice.righe){
			printf("Inserire la colonna: ");
			scanf("%d", &colonna); fflush(stdin);
			if (colonna > -1 && colonna < matrice.colonne){
				printf("Inserire il valore: "); fflush(stdin);
				scanf("%f", &valore);
				inserisci(&matrice, riga, colonna, valore);
			} else riga = -1;
		} else riga = -1;
	}
	printf("Matrice: \n");
	
	stampa(&matrice);
	
	printf("Termino esecuzione.\n");
	
	return 0;
}

void init(matr_t* matrice, int righe, int colonne){
	matrice->righe = righe;
	matrice->colonne = colonne;
	matrice->righe_liste = malloc(righe*sizeof(node_t*));
	matrice->sentinella = malloc(sizeof(node_t*));
	for(int riga = 0; riga < righe; riga++) matrice->righe_liste[riga] = matrice->sentinella;
}

node_t* nodo(int colonna, float valore, node_t* prossimo_nodo){
	node_t* nodo = malloc(sizeof(node_t));
	nodo->colonna = colonna;
	nodo->valore = valore;
	nodo->prossimaColonna = prossimo_nodo;
	return nodo;
}

void inserisciRicorsivo(node_t* listaRiga, node_t* sentinella, int colonna, float valore){
	node_t* mioNodo;
	if (listaRiga->prossimaColonna == sentinella){
		mioNodo = nodo(colonna, valore, listaRiga->prossimaColonna);
		listaRiga->prossimaColonna = mioNodo;
		return;
	}
	
	if (listaRiga->prossimaColonna->colonna > colonna){
		mioNodo = nodo(colonna, valore, listaRiga->prossimaColonna);
		listaRiga->prossimaColonna = mioNodo;
		return;
	}
	
	inserisciRicorsivo(listaRiga->prossimaColonna, sentinella, colonna, valore);
}

void inserisci(matr_t* matrice, int riga, int colonna, float valore){
	node_t* listaRiga = matrice->righe_liste[riga];
	node_t* mioNodo;
	if (listaRiga == matrice->sentinella){
		mioNodo = nodo(colonna, valore, matrice->sentinella);
		matrice->righe_liste[riga] = mioNodo;
		return;
	}
	
	if (listaRiga->prossimaColonna == matrice->sentinella)
		if (colonna < listaRiga->colonna){
			mioNodo = nodo(colonna, valore, listaRiga);
			matrice->righe_liste[riga] = mioNodo;
			return;
		}
		
	inserisciRicorsivo(listaRiga, matrice->sentinella, colonna, valore);
}


void stampa(matr_t* matrice){
	int riga, colonna;
	node_t* nodoRiga;
	for(riga = 0; riga < matrice->righe; riga++){
		nodoRiga = matrice->righe_liste[riga];
		for(colonna = 0; colonna < matrice->colonne; colonna++){
			if (nodoRiga != matrice->sentinella){
				if (nodoRiga->colonna == colonna) {
					printf("%.2f ", nodoRiga->valore);
					nodoRiga = nodoRiga->prossimaColonna;
				}
				else printf("%.2f ", (float)0);
			} else printf("%.2f ", (float)0);
		}
		printf("\n");
	}
}
