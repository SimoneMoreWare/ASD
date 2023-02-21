/*
Sia U l’insieme degli interi compresi 1 e 8: U= 1, 2, 3, 4, 5, 6, 7, 8. Sia S una matrice n x 9 di interi che su
ciascuna delle n righe contiene un sottoinsieme di U terminato dal valore 0. La matrice viene ricevuta da una
funzione come parametro formale con numero di righe ignoto. Il numero di righe compare come ulteriore
parametro. Dato un intero k, ulteriore parametro della funzione, si scriva una funzione ricorsiva in C che
visualizzi, se esiste, una collezione di k sottoinsiemi la cui unione sia U. La funzione abbia il seguente prototipo:
void cover(int S[][9], int n, int k);

*/
#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 8

int checksol(int s[][9], int k, int n, int* sol, int* solfin,int *u);
void cover(int s[][9], int n, int k);
void coverR(int pos, int* sol, int* solfin, int start, int s[][9], int n, int k,int *u);
void initu(int s[][9], int* u);
void addelem(int* s, int* u);
int check(int val, int* u);
void selectionsort(int* A);

int main()
{
	int S[N][9]=
	{ 
		{1,2,3,0,0,0,0,0,0},
		{2,3,7,0,0,0,0,0,0},
		{7,8,0,0,0,0,0,0,0},
		{3,4,0,0,0,0,0,0,0},
		{4,5,6,0,0,0,0,0,0} 
	};
	cover(S, N, 3);
	return 0;
}
void cover(int s[][9], int n, int k)
{
	int i;
	int* u = calloc(8, sizeof(int));
	int* sol = calloc(k , sizeof(int));
	int* solfin = calloc(k , sizeof(int));
	initu(s, u);    //PARTO A CALCOLARE INSIEME U SICCOME NON HO A DISPOSIZIONE 
	                //QUESTA SOLUZIONE PROPONE DI CALCOLARE PRIMA INSIEME U all'inizio tale da rendere più facile nella fase di check della ricorsione
	selectionsort(u);
	coverR(0, sol, solfin, 0, s, n, k,u);

}

void coverR(int pos, int* sol, int* solfin, int start, int s[][9], int n, int k,int *u)
{
	int i,j;
	if (pos == k)
	{
		if(checksol(s, k, n, sol, solfin,u)==1)
		{
			printf("sol : ");
			for (j = 0; j < k; j++)
			{
				printf("S%d ", sol[j]+1);
			}
			printf("\n");
		}
		return;
	}
	for (i = start; i < n; i++)
	{
		sol[pos] = i;
		coverR(pos + 1, sol, solfin, i + 1, s, n, k,u);
	}

}
int checksol(int s[][9], int k, int n, int* sol, int* solfin,int *u)
{
	
	int i, j, isvalid = 1;
	int key[M] = {0};
	for (i = 0; i < k; i++)
	{
		addelem(s[sol[i]], key);
	}

	selectionsort(key);

	for (i = 0; i < 8; i++)
	{
		if (key[i] != u[i])
		{
			isvalid = 0;
			break;
		}
	}
	return isvalid;
}

void initu(int s[][9], int* u)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		addelem(s[i], u);
	}
}
void addelem(int* s, int* u)
{
	int j=0;
	int i;
	for (i = 0; i < M; i++)
	{
		if (u[i] != 0)
			j++;
	}
	for (i = 0; i < 9&&j<M; i++)
	{
		if (check(s[i], u))
			u[j++] = s[i];
		
	}
}
int check(int val, int* u)
{
	int ok = 1;
	int i;
	for (i = 0; i < M; i++)
	{
		if (val == u[i])
		{
			ok = 0;
			break;
		}
		
	}
	return ok;
}
void selectionsort(int* A)
{
	int i, j, min, tmp;
	for (i = 0; i < M; i++)
	{
		min = i;
		for (j = i + 1; j < M; j++)
		{
			if (A[j] < A[min])
				min = j;
		}
		tmp = A[i];
		A[i] = A[min];
		A[min] = tmp; 
	}
}
