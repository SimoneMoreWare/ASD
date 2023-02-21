#include <stdio.h>
#include <stdlib.h>

#define MAX_CARD 10+1

void genera(FILE* fileLettura, FILE* fileScrittura);

int main(int argc, char **argv)
{
	FILE* fileLettura, *fileScrittura;
	printf("Inizio esecuzione.\n");
	printf("Apro i file...");
	fileLettura = fopen("file.txt", "r");
	fileScrittura = NULL; // fopen()...
	printf("File aperti.\n");
	if (fileLettura == NULL) {
		printf("File di lettura non aperto correttamente.\n");
		return -420;
	}
	
	//if (fileScrittura)...
	
	genera(fileLettura, fileScrittura);
	
	return 420;
}

void mult(int posizione, int massimo, char* stringa, char** insiemi){
	int i;
	if (posizione >= massimo){
		printf("\n");
		for(i=0; i<massimo; i++) printf("%c", stringa[i]); // Ok qui sarebbe su file,
		return;										//Ma printf , fprintf stiamo là
	}
	for(i=0; insiemi[posizione][i] != '\0'; i++){
		stringa[posizione] = insiemi[posizione][i];
		mult(posizione+1, massimo, stringa, insiemi);
	}
}

void genera(FILE* fileLettura, FILE* fileScrittura){
	int n, i, j;
	char** insiemi, carattere, *selezioni;
	//Assumo i file aperti correttamente
	printf("Avvio lettura.\n");
	fscanf(fileLettura, "%d\n", &n); printf("%d righe da leggere.\n", n);
	insiemi = malloc(n*sizeof(char*));
	for (i=0; i<n; i++) {
		insiemi[i] = malloc(MAX_CARD*sizeof(char));
		j = 0;
		carattere = '.';
		while(carattere != '\0' && carattere != '\n' && carattere != EOF && j < MAX_CARD-1){
			if (fscanf(fileLettura, "%c" , &carattere) == EOF) carattere = EOF;
			if (carattere != '\0' && carattere != '\n' && carattere != EOF) {
				insiemi[i][j] = carattere;
				j++;
			}
		}
		insiemi[i][j] = '\0';
	}
	
	printf("Lettura completata.\n");
	
	selezioni = malloc(n*sizeof(char));
	
	printf("Inizio stampa.\n");
	mult(0, n, selezioni, insiemi);
	printf("\n");
	// free()....
}