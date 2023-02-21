#include <stdio.h>
#include <stdlib.h>
#define R 5
#define C R

int** leggimatr(char* filename, int* r, int* c);
void sommacornici(int** mat, int N, int** vet);
int calcolasomma(int** mat, int x, int y, int r,int k);

int main()
{
	int* vet;
	int** matr;
	int r, c;
	matr = leggimatr("matr.txt", &r, &c);
	int N = R - 2;
	if (N > 1)
	{
		sommacornici(matr, N, &vet);
	}
	else
	{
		printf("non è una matrice\n");
	}
	return 0;

}
int** leggimatr(char* filename, int* r, int* c)
{
	int i, j;
	FILE* fp;
	fp = fopen(filename, "r");
	fscanf(fp, "%d %d", r, c);
	int** matr;
	matr = calloc(R, sizeof(int*));
	for (i = 0; i < R; i++)
		matr[i] = calloc(C, sizeof(int));
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			fscanf(fp, "%d", &matr[i][j]);
		}

	}
	return matr;

}

void sommacornici(int** mat, int N, int** vet)
{
	(*vet) = calloc(N, sizeof(int));
	int i=0, j=0, k=0,r=R;
	if (R % 2 > 0)
	{
		while (i != N && j != N && k != N && r != 1)
		{
			(*vet)[k++] = calcolasomma(mat, i, j, r,k);
			r = r - 2;
			i++;
			j++;
		}
		(*vet)[k] = mat[i][j];
		for (i = 0; i < N; i++)
		{
			printf("%d ", (*vet)[i]);
		}
	}
	else
	{
		while (i != N && j != N && k != N && r != 0)
		{
			(*vet)[k++] = calcolasomma(mat, i, j, r, k);
			r = r - 2;
			i++;
			j++;
		}
		for (i = 0; i < N; i++)
		{
			printf("%d ", (*vet)[i]);
		}
	}

}
int calcolasomma(int** mat, int x, int y, int r,int k)
{
	int first=0, sec=0, th=0, fh=0;
	int i, j;
	for (i = y; i < r+k; i++)
	{
		first = first + mat[x][i];
		sec = sec + mat[x + r - 1][i];
	}
	for (i = x + 1; i < r - 1+k; i++)
	{
		th = th + mat[i][y];
		fh = fh + mat[i][y + r - 1];
	}
	return (first + sec + th + fh);

}
