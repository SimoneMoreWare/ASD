#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3 // Se lo cambiate dovete aggiornare la funzione vettore()
#define STRLEN 20+1

typedef char* Piatto;
typedef char** Portata;  // Scusate sta roba, ma stavo
typedef char*** Menu;	//	Diventando coglione

Menu data(){
	Menu piatti;
	piatti = malloc(N*sizeof(Portata));
	
	piatti[0] = malloc(3*sizeof(Piatto));
		(piatti[0])[0] = malloc(STRLEN*sizeof(char));
		(piatti[0])[1] = malloc(STRLEN*sizeof(char));
		(piatti[0])[2] = NULL;
		
		strcpy((piatti[0])[0], "pasta");
		strcpy((piatti[0])[1], "riso");
		
	piatti[1] = malloc(4*sizeof(Portata));
		(piatti[1])[0] = malloc(STRLEN*sizeof(char));
		(piatti[1])[1] = malloc(STRLEN*sizeof(char));
		(piatti[1])[2] = malloc(STRLEN*sizeof(char));
		(piatti[1])[3] = NULL;
		
		strcpy((piatti[1])[0], "carne");
		strcpy((piatti[1])[1], "pesce");
		strcpy((piatti[1])[2], "formaggio");
		
	piatti[2] = malloc(3*sizeof(Piatto));
		(piatti[2])[0] = malloc(STRLEN*sizeof(char));
		(piatti[2])[1] = malloc(STRLEN*sizeof(char));
		(piatti[2])[2] = NULL;
		
		strcpy((piatti[2])[0], "gelato");
		strcpy((piatti[2])[1], "torta");
		
	return piatti;
}
void mult(Menu menu, Portata scelte, int numeroScelte, int posizione){
	int i;
	Portata possibiliScelte = menu[posizione];
	if (posizione >= numeroScelte){
		printf("Possibilita': {");
		for(i=0; i<numeroScelte; i++)
			printf(" %s, ", scelte[i]);
		printf("}\n");
		return;
	}
	for(i=0; possibiliScelte[i] != NULL; i++){
		scelte[posizione] = possibiliScelte[i];
		mult(menu, scelte,numeroScelte, posizione+1);
	}
	
}

int main(int argc, char **argv)
{
	int i;
	
	printf("Inizio esecuzione.\n");
	printf("Genero il menu...\n");
	Menu menu = data();
	printf("Menu generato.\n");
	printf("Genero il \"vassoio\".\n");
	Portata portata = malloc(sizeof(Portata));
	for(i=0; i<N;i++) portata[i] = malloc(sizeof(Piatto));
	printf("\"Vassoio\" generato.\n");
	
	printf("Genero le possibili portate...\n");
	mult(menu, portata, N, 0);
	printf("Termino esecuzione.\n");
	
	return 0;
}
