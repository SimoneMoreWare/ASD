#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // <-- Se siete su Windows commentare questo [opzionale]

#define N 3

int** matrice(int n);
void cercaInsiemeMinimo(int** matrice, int n);

int main(int argc, char **argv)
{
	srand(getpid()); // <-- Se siete su Windows commentare questo
	int** miaMatrice = matrice(N);
	cercaInsiemeMinimo(miaMatrice, N);
	
	return 420;
}

int** matrice(int n){
	int i, j;
	printf("Matrice: \n");
	int** matrice = malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
		matrice[i] = malloc(n*sizeof(int));
		for(j=0; j<n; j++) {
			matrice[i][j] = rand() % 2; // (i+j) % 2;  <-- Se siete su Windows usare questo
			printf("%d ", matrice[i][j]);
		}
		printf("\n");
	}
	
	return matrice;
}

int funzioneDiControllo(int **matrice, int *scelteRighe, int* scelteColonne, int n){
	int i, j, **falsaMatrice;
	
	falsaMatrice = malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
		falsaMatrice[i] = malloc(n*sizeof(int));
		for(j=0; j<n; j++) falsaMatrice[i][j] = matrice[i][j];
	}
	
	for(i=0; i<n; i++){
		if (scelteRighe[i]) for(j=0; j<n; j++) falsaMatrice[i][j] = !falsaMatrice[i][j];
	}
	for(i=0; i<n; i++){
		if (scelteColonne[i]) for(j=0; j<n; j++) falsaMatrice[j][i] = !falsaMatrice[j][i];
	}
	
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			if (!falsaMatrice[i][j]){
				for(i=0; i<n; i++) free(falsaMatrice[i]);
				free(falsaMatrice);
				return 0;
			}
	for(i=0; i<n; i++) free(falsaMatrice[i]);
	free(falsaMatrice);
	return 1;
}

void cercaR(int pos, int **matrice, int* flagTrovato, int n, int maxScelte, int scelteAttuali, int* scelteRighe, int* scelteColonne){
	int i;
	if ( *flagTrovato ) return;
	if (pos >= n || scelteAttuali == maxScelte){
		if (funzioneDiControllo(matrice, scelteRighe, scelteColonne, n)){
			*flagTrovato = 1;
			printf("Trovata una soluzione.\n");
			printf("Righe: ");
			for(i=0; i<n; i++) if (scelteRighe[i]) printf("%d ", i);
			printf("\nColonne: ");
			for(i=0; i<n; i++) if (scelteColonne[i]) printf("%d ", i);
			printf("\n");
		}
		return;
	}
	scelteRighe[pos] = 1; // 1 0 
	cercaR(pos+1, matrice, flagTrovato, n, maxScelte, scelteAttuali+1, scelteRighe, scelteColonne);
	scelteColonne[pos] = 1; // 1 1 
	cercaR(pos+1, matrice, flagTrovato, n, maxScelte, scelteAttuali+2, scelteRighe, scelteColonne);
	scelteRighe[pos] = 0;  // 0 1
	cercaR(pos+1, matrice, flagTrovato, n, maxScelte, scelteAttuali+1, scelteRighe, scelteColonne);
	scelteColonne[pos] = 0; // 0 0 
	cercaR(pos+1, matrice, flagTrovato, n, maxScelte, scelteAttuali, scelteRighe, scelteColonne);
}

void cercaInsiemeMinimo(int** matrice, int n){
	int *switchRighe = calloc(n, sizeof(int));
	int *switchColonne = calloc(n, sizeof(int));
	int flagTrovato = 0;
	int i;
	for(i=0; i<=n*n && !flagTrovato; i++) cercaR(0, matrice, &flagTrovato, n, i, 0, switchRighe, switchColonne);
	if (!flagTrovato) printf("Non e' stato possibile trovare una soluzione.\n");
	free(switchColonne);
	free(switchRighe);
	return;
}