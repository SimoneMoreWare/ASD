#include <stdio.h>
#include <stdlib.h>

#define R 3
#define C 4
#define K 11

int** generaMatrice(int r, int c, int vuota);
void disp2D(int** matrice, int** scelte, int** bestSol, int maxScelte, int scelteAttuali, int k, int *flag, int righe, int colonne, int posR, int posC);
void cerca(int** mat, int r, int c, int k);


int main(int argc, char **argv){
	int** matrice = generaMatrice(R, C, 0);
	printf("\nCerco elementi la cui somma dia %d\n\n", K);
	cerca(matrice, R, C, K);
	printf("\n");
	return 0;
}



int** generaMatrice(int r, int c, int vuota){
	int i, j, **matrice;
	
	matrice = malloc(r*sizeof(int*));
	for(i=0; i<r; i++){
		matrice[i] = malloc(c*sizeof(int));
		for(j=0; j<c; j++){
			if (!vuota) matrice[i][j] = rand() % 10;
			else matrice[i][j] = 0;
			if (!vuota) printf("%d ", matrice[i][j]);
		}
		if (!vuota) printf("\n");
	}
	
	return matrice;
}

int sum(int** matrice, int** scelte, int righe, int colonne){
	int i, j, sum = 0;
	for(i=0; i<righe; i++) for(j=0; j<colonne; j++) if (scelte[i][j]) sum += matrice[i][j];
	return sum;
}

void disp2D(int** matrice, int** scelte, int** bestSol, int maxScelte, int scelteAttuali, int k, int *flag, int righe, int colonne, int posR, int posC){
	if ( *flag ) return;
	int sumM, i, j;
	if (posR == righe || posC == colonne){
		if (scelteAttuali == maxScelte){
		sumM = sum(matrice, scelte, righe, colonne);
		if (sumM == k){
			*flag = scelteAttuali;
			for(i=0; i<righe; i++) for(j=0; j<colonne; j++) bestSol[i][j] = scelte[i][j];
		}
		}
		return;
	}
	scelte[posR][posC] = 0;
	disp2D(matrice, scelte, bestSol, maxScelte, scelteAttuali, k, flag, righe, colonne, posR+1, posC); 
	disp2D(matrice, scelte, bestSol, maxScelte, scelteAttuali, k, flag, righe, colonne, posR, posC+1); 
	scelte[posR][posC] = 1;
	disp2D(matrice, scelte, bestSol, maxScelte, scelteAttuali+1, k, flag, righe, colonne, posR+1, posC); 
	disp2D(matrice, scelte, bestSol, maxScelte, scelteAttuali+1, k, flag, righe, colonne, posR, posC+1);
	scelte[posR][posC] = 0;
}

void cerca(int** mat, int r, int c, int k){
	int** scelte = generaMatrice(r, c, 1);
	int** soluzione = generaMatrice(r, c, 1);
	int flag = 0;
	int i, j;
	for(i=1; i<=r*c && flag == 0; i++)
		disp2D(mat, scelte, soluzione, i, 0, k, &flag, r, c, 0, 0);
	if (flag > 0){
		printf("Soluzione a cardinalita' minima (%d): ", flag);
		printf("\n{");
		for(i=0; i<r; i++)
			for(j=0; j<c; j++)
				if (soluzione[i][j]) printf(" (%d,%d) ", i, j);
		printf("}\n");
	}
	else printf("\nNon e' stata trovata soluzione.\n");
	flag = 0;
	for(i=r*c; i >= 0 && flag == 0; i--)
		disp2D(mat, scelte, soluzione, i, 0, k, &flag, r, c, 0, 0);
	if (flag > 0){
		printf("Soluzione a cardinalita' massima (%d): ", flag);
		printf("\n{");
		for(i=0; i<r; i++)
			for(j=0; j<c; j++)
				if (soluzione[i][j]) printf(" (%d,%d) ", i, j);
		printf("}\n");
	}
	else printf("\nNon e' stata trovata soluzione.\n\n");
	
	return;
}