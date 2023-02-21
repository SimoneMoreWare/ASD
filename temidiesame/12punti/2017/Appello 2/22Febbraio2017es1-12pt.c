#include <stdio.h>
#include <stdlib.h>

#define R1 6
#define C1 4
#define R2 5
#define C2 7
#define X 2
#define Y 0

int** matriceRandom(int righe, int colonne);
void printMat(int** mat, int righe, int colonne);
void overwrite(int **m1, int r1, int c1, int **m2, int r2, int c2, int x, int y);

int main(int argc, char **argv){
	int **matrice1, **matrice2;
	printf("Matrice I: \n");
	matrice1 = matriceRandom(R1, C1);
	printf("Matrice II: \n");
	matrice2 = matriceRandom(R2, C2);
	
	printf("Sovrascrivo Matrice I con Matrice II a partire da (%d, %d)\n", X, Y);
	overwrite(matrice1, R1, C1, matrice2, R2, C2, X, Y);
	printMat(matrice1, R1, C1);
}

int** matriceRandom(int righe, int colonne){
	int** matrice, i, j;
	matrice = malloc(righe*sizeof(int*));
	for(i=0; i<righe; i++){
		matrice[i] = malloc(colonne*sizeof(int));
		for(j=0; j<colonne; j++){
			matrice[i][j] = rand() % 10;
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
	return matrice;
}

void printMat(int** mat, int righe, int colonne){
	for(int i=0; i<righe; i++){
		for(int j=0; j<colonne; j++) printf("%d ", mat[i][j]);
		printf("\n");
	}
}

void overwrite(int **m1, int r1, int c1, int **m2, int r2, int c2, int x, int y){
	int i, j;
	int right, down;
	if ( y + c2 - 1 < c1) right = y + c2 -1;
	else right = c1-1;
	if ( x + r2 - 1 < r1) down = x + r2 - 1;
	else down = r1-1;
	
	for(i=x; i<= down; i++)
		for(j=y; j<= right; j++)
			m1[i][j] = m2[i-x][j-y];
}