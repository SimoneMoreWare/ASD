/*
Nel primo quadrante del piano cartesiano è individuata una regione quadrata i cui vertici in basso a sinistra e in alto a destra
hanno coordinate (0,0) e (100,100). In un file è descritta una sequenza di rettangoli con i lati paralleli agli assi cartesiani.
Ogni rettangolo è individuato dalle coordinate dei vertici in basso a sinistra e in alto a destra. Le coordinate sono interi
compresi tra 0 e 100, estremi inclusi. Scrivere la funzione int areaTot(FILE *fp); che riceve come parametro un
puntatore al file (già aperto) e restituisce il valore totale dell’area coperta dai rettangoli. Nel caso di intersezione di
rettangoli l’area è contata una sola volta.
Esempio (semplificato con coordinate x e y nell’intervallo (0..10): se il file contiene sulla prima riga 1 2 4 4 e sulla seconda
3 3 5 8, l’area coperta vale 15.

*/
#include <stdio.h>
#include <stdlib.h>
#define R 10+1 //per semplicità si assume quadrante di dim 10*10
#define C R

int areatot(FILE* fp);

int main()
{
	int area;
	FILE* fp;
	fp = fopen("test.txt", "r");
	if (fp == NULL)
		exit(0);
	area = areatot(fp);
	printf("area tot è: %d", area);
	return 0;
}

int areatot(FILE* fp)
{
	int i, j,area=0;
	int x1, x2, y1, y2;
	int** tab;
	tab = calloc(R, sizeof(int*));
	for (i = 0; i < R; i++)
		tab[i] = calloc(C, sizeof(int));
	while (fscanf(fp, "%d %d %d %d", &x1, &y1, &x2, &y2) == 4)
	{
		for (i = x1; i < x2; i++)
		{
			for (j = y1; j < y2; j++)
			{
				tab[i][j]++;
			}
		}
	}
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			if (tab[i][j] != 0)
			{
				tab[i][j] = 1;
			}
		}
	}
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			if (tab[i][j] != 0)
			{
				area += tab[i][j];
			}
		}
	}
	return area;
}
