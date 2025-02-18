#include <stdio.h>
#include <stdlib.h>

/*
 * la struttura definisce un array dinamico
 *
 * dim = dimensione variabile dell'array
 * array = vettore di puntatori a valori interi
 */
typedef struct {
    int dim;
    int* array;
} array_dinamico;

/*
 * alloca in maniera dinamica una matrice a partire da un file
 *
 * file = nome del file 
 * nr = numero di righe della matrice
 * nc = numero di colonne della matrice
 * 
 * ritorna la matrice popolata con i puntatori a valori interi ottenuti dal file
 */
int** malloc2dR(FILE* file, int nr, int nc);

/*
 * separa la matrice in "celle bianche" e "celle nere"
 *
 * mat = matrice di puntatori a valori interi
 * nr = numero di righe della matrice
 * nc = numero di colonne della matrice
 * vettB = vettore delle "celle bianche"
 * vettN = vettore delle "celle nere"
 */
void separa(int** mat, int nr, int nc, array_dinamico vettB, array_dinamico vettN);

int main() {
    char* nomeFile = "mat.txt";
    FILE* file;
    if ((file = fopen(nomeFile, "r")) == NULL) {
        printf("Non e' stato possibile aprire il file.");
        return 1;
    }
    
    int nr, nc;
    if(!feof(file)) {
		fscanf(file, " %d %d ", &nr, &nc);
	} else {
		printf("Il file e' vuoto.\n");
		return 2;
	}
    int** mat = malloc2dR(file, nr, nc);

    array_dinamico vettB, vettN;
    /*
     * la dimensione del vettore per le "celle bianche"
     * è sempre almeno uguale alla dimensione del vettore 
     * per le "celle nere", ma viene aumentata di 1 
     * quando nr e nc sono dispari per contare la "cella bianca" 
     * aggiuntiva
     */
    vettB.dim = vettN.dim = (nr*nc)/2;
    if(nr%2 == 1 && nc%2 == 1)
        vettB.dim++;
    vettB.array = (int*) malloc(vettB.dim*sizeof(int));
    vettN.array = (int*) malloc(vettN.dim*sizeof(int));

    separa(mat, nr, nc, vettB, vettN);

    int i;
    printf("Valori delle posizioni bianche: ");
    for(i = 0; i < vettB.dim; i++) {
        printf("%d ", vettB.array[i]);
    }
    printf("\n");
    free(vettB.array);

    printf("Valori delle posizioni nere: ");
    for(i = 0; i < vettN.dim; i++) {
        printf("%d ", vettN.array[i]);
    }
    free(vettN.array);

    for(i = 0; i < nr; i++) {
        free(mat[i]);
    }
    free(mat);
    return 0;
}

int** malloc2dR(FILE* file, int nr, int nc) {
    int i, j;
    int** mat = (int**) malloc(nr*sizeof(int*));
    for(i = 0; i < nr; i++) {
        mat[i] = (int*) malloc(nc*sizeof(int));
        for(j = 0; j < nc; j++) {
            fscanf(file, " %d ", &mat[i][j]);
        }
    }
    return mat;
}

void separa(int** mat, int nr, int nc, array_dinamico vettB, array_dinamico vettN) {
    int i, j, posB = 0, posN = 0;
    for(i = 0; i < nr; i++) {
        for(j = 0; j < nc; j++) {
            if((i+j)%2 == 0) {
                vettB.array[posB] = mat[i][j];
                posB++;
            }
            else {
                vettN.array[posN] = mat[i][j];
                posN++;
            }
        }
    }
}
