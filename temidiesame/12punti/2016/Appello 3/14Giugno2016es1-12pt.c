/*
Scrivere una funzione
void matMax (int **m, int r, int c);
che riceve una matrice m di interi di r righe e c colonne e visualizza (a video) la posizione di tutti gli elementi
che sono strettamente maggiori di tutti gli elementi adiacenti. Ad esempio, data la matrice seguente:
matr.txt:
5 2 3 1
4 1 6 4
3 0 5 2

occorre visualizzare: (0, 0) e (1, 2).

*/
#include <stdio.h>
#include <stdlib.h>
#define R 3
#define C 4
void matmax(int** m, int r, int c);
int check(int** m, int r, int c,int x, int y, int val);

int main()
{
	FILE* fp;
	int i, j;
	int** m;
	m = calloc(R, sizeof(int*));
	for (i = 0; i < R; i++)
		m[i] = calloc(C, sizeof(int));
	fp = fopen("matr.txt", "r");
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
			fscanf(fp, "%d", &m[i][j]);
	}

	matmax(m, R, C);
}

void matmax(int** m, int r, int c)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			if (check(m, r, c, i, j, m[i][j]))
				printf("%d ", m[i][j]);
		}
	}
}
int check(int** m, int r, int c, int x, int y, int val)
{
	int ok = 1;
	int okdef;
	if (x + 1 < R)
	{
		if (m[x + 1][y] > val)
		{
			ok = 0;

		}
	}
	if (x - 1 >= 0)
	{
		if (m[x -1][y] > val)
		{
			ok = 0;

		}
	}
	if (y + 1 < C)
	{
		if (m[x][y+1] > val)
		{
			ok = 0;

		}
	}
	if (y - 1 >= 0)
	{
		if (m[x][y -1] > val)
		{
			ok = 0;

		}
	}
	return ok;
	
}
