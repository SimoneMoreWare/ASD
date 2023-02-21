#include <stdio.h>
#include <stdlib.h>
#define R 3
#define C 3

void powerset(int pos, int matr[R][C], int* sol, int k,int*minimo,int *bestsol,int **matrsup);
void check(int matr[R][C], int* sol, int k,int *minimo,int **matrsup,int *bestsol);
void changeriga(int** matrsup, int riga);
void changecolonna(int** matrsup, int colonna);

int main()
{
	int i, j;
	int k = R + C;
	int matr[R][C] =
	{
		{0,1,0},
		{1,0,1},
		{0,1,0}
	};
	int* sol = calloc(k, sizeof(int));  //indice 0: commutazione riga1,indice 1:commutazione riga 1.....indce 3: commutazione colonna 0...
	int* bestsol = calloc(k, sizeof(int));
	int minimo = 7;
	int** matrsup;
	matrsup = calloc(R, sizeof(int*));
	for (i = 0; i < R; i++)
		matrsup[i] = calloc(C, sizeof(int));

	powerset(0, matr, sol, k, &minimo, bestsol,matrsup);
	printf("%d\n", minimo);
	for (i = 0; i < k; i++)
	{
		if (i <= 2)
		{
			if (bestsol[i] == 1)
				printf("riga %d\n", i);
		}
		else
		{
			if (bestsol[i] == 1)
				printf("colonna %d\n", i - 2);
		}
	}
	return 0;

}
void powerset(int pos, int matr[R][C], int* sol, int k, int* minimo, int* bestsol,int **matrsup)
{
	int i;
	if (pos >= k)
	{
		check(matr, sol, k, minimo, matrsup,bestsol);
		return;
	}

	sol[pos] = 0;
	powerset(pos + 1, matr, sol, k, minimo, bestsol,matrsup);
	sol[pos] = 1;
	powerset(pos + 1, matr, sol, k, minimo, bestsol,matrsup);
}
void check(int matr[R][C], int* sol, int k, int* minimo,int **matrsup,int* bestsol)
{
	int minimoloc=0;
	int ok = 1;
	int i, j;
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			matrsup[i][j] = matr[i][j];
		}
	}
	for (i = 0; i < k; i++)
	{
		if (i<=2)
		{
			if (sol[i] == 1)
				changeriga(matrsup, i);
		}
		else
		{
			if (sol[i] == 1)
				changecolonna(matrsup, i - 2);
		}

	}
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			if (matrsup[i][j] != 1)
			{
				ok = 0;
				break;
			}
		}
		if (ok == 0)
		{
			break;
		}
	}
	
	if (ok == 1)
	{
		for (i = 0; i < k; i++)
		{
			if (sol[i] == 1)
				minimoloc++;
		}
		if (minimoloc < *minimo)
		{
			*minimo = minimoloc;
			for (i = 0; i < k; i++)
				bestsol[i] = sol[i];
		}
		return ok;
	}
	
	return ok;
}

void changeriga(int** matrsup, int riga)
{
	int  j;
	for (j = 0; j < C; j++)
		matrsup[riga][j] = !(matrsup[riga][j]);
	return;
}

void changecolonna(int** matrsup, int colonna)
{
	int i;
	for(i=0;i<R;i++)
		matrsup[i][colonna] = !(matrsup[i][colonna]);
	return;
}
