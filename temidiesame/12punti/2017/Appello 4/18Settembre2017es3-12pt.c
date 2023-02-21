#include <stdio.h>
#include <stdlib.h>
/*
P piattaforme, disposte in sequenza in linea retta, sono caratterizzate ognuna da un intero positivo. Ognuno di
essi indica la lunghezza massima del salto verso destra che può fare il giocatore che si trova su quella
piattaforma. Non sono permessi salti all’indietro (verso sinistra).
Si scriva una funzione in grado di determinare, se esiste, una sequenza ottima di salti che il giocatore deve fare
per spostarsi dalla piattaforma di partenza (indice 0, estremo sinistro) a quella di arrivo (indice P-1, estremo
destro). Criterio di ottimalità: minimo numero di salti.

*/
#define P 5

int visitandfind(int** matr, int p,int count);

int main()
{
	int count;
	int i,j,k,max=0;
	int val[P] = { 3,2,1,1,1 };
	int **matadiacenza;
	matadiacenza = calloc(P, sizeof(int*));
	for (i = 0; i < P; i++)
	{
		matadiacenza[i] = calloc(P, sizeof(int));
	}
	for (i = 0; i < P - 1; i++)
	{
		k = 1;
		for (j = i+1; j <P&&k<=val[i]; j++)
		{
			matadiacenza[i][j] = k;
			k++;
		}
	}
	count=visitandfind(matadiacenza, P-1,0);
	printf("\n %d salti", count);

	return 0;

}


int visitandfind(int** matr, int p,int count)
{
	if (p == 0)
	{
		return count;
	}
	int max = 0;
	int i;
	int j;
	for (i = p; i >= 0; i--)
	{
		if (matr[i][p] > max)
		{
			max = matr[i][p];
			j = i;
		}
	}
	printf("da %d con peso %d\n", j, max);
	count=visitandfind(matr, j, count+1);
	return count;
}
