#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 5

void comb_semplice(int pos, int vet[N], int* sol, int n, int k, int start);
int check(int vet[N], int *sol,int n, int k);

int main()
{
	int k = 3;
	int vet[N] = { 2,1,1,4,3 };
	int* sol = calloc(k, sizeof(int));
	comb_semplice(0, vet, sol, N, k, 0);

	return 0;
}

void comb_semplice(int pos, int vet[N], int* sol, int n, int k, int start)
{
	int i;
	if (pos >= k)
	{
		if (check(vet, sol, n, k))
		{
			printf("(");
			for (i = 0; i < k; i++)
			{
				printf("%d ", sol[i]);
			}
			printf(") ");
		}
		return;
	}

	for (i = start; i < n; i++)
	{
		sol[pos] = i;
		comb_semplice(pos + 1, vet, sol, n, k, start++);
	}
	return;
}

int check(int vet[N], int* sol, int n, int k)
{
	
	int i;
	int ok = 1;
	int* mark = calloc(M, sizeof(int));

	for (i = 0; i < k; i++)
	{
		(mark[vet[sol[i]]])++;
	}

	for (i = 0; i < M; i++)
	{
		if (mark[i] != 0 && mark[i] != 1)
		{
			ok = 0;
			break;
		}
	}

	return ok;
}
