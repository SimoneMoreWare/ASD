/*
In un campionato n squadre giocano per m giornate. Sia data una matrice C di n × m numeri interi,
ognuno dei quali può valere soltanto 0, 1 o 3. Ogni riga della matrice rappresenta i punti acquisiti dalle
n squadre nelle partite disputate nelle m giornate del campionato: 3 punti per le partite vinte, 1 punto
per quelle pareggiate e 0 punti per le sconfitte. I risultati della giornata k-esima sono contenuti nelle
righe della colonna di indice k. Si scriva una funzione C con il seguente prototipo
void displRanking(int **C, int n, int m);
che, per ogni giornata del campionato, stampi l'indice (il numero di riga corrispondente) della squadra
capolista in quella giornata.
*/

#include <stdio.h>
#include<stdlib.h>
#define N 4
#define M 3

void stamparanking(int C[N][M], int n, int m);

int main()
{
	int C[N][M] =
	{
		{3,1,0},
		{0,1,1},
		{1,1,1},
		{1,1,3}
	};

	stamparanking(C, N, M);
	return 0;
}
void stamparanking(int C[N][M], int n, int m)
{
	int i, j;
	int max = -1;
	int maxi = -1;
	for (j = 0; j < M; j++)
	{
		for (i = 0; i < N; i++)
		{
			if (C[i][j] > max)
			{
				max = C[i][j];
				maxi = i;
			}
		}
		printf("%d ", maxi);
		maxi = -1;
		max = -1;
	}
	return;
}
