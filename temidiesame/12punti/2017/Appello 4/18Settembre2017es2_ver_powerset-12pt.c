/* 
P piattaforme, disposte in sequenza in linea retta, sono caratterizzate ognuna da un intero positivo. Ognuno di
essi indica la lunghezza massima del salto verso destra che può fare il giocatore che si trova su quella
piattaforma. Non sono permessi salti all’indietro (verso sinistra).
Si scriva una funzione in grado di determinare, se esiste, una sequenza ottima di salti che il giocatore deve fare
per spostarsi dalla piattaforma di partenza (indice 0, estremo sinistro) a quella di arrivo (indice P-1, estremo
destro). Criterio di ottimalità: minimo numero di salti.
Esempio
Con P = 5 e la seguente configurazione di piattaforme:


*/


#include <stdio.h>
#include <stdlib.h>

#define P 5

void powerset(int pos, int* val, int* sol, int n, int* minimo, int* bestsol);
void check(int* sol,int*val, int n, int *minimo, int* bestsol);

int main()
{
	int i;
	int val[P] = { 3,2,2,1,1 };
	int* sol = calloc(P, sizeof(int));
	sol[0] = 1;
	int *bestsol= calloc(P, sizeof(int));
	int minimo = P + 1;
	powerset(1, val, sol, P, &minimo, bestsol);
	printf("%d", minimo);
	printf("\n");
	for (i = 0; i < P; i++)
	{
		printf("%d ", bestsol[i]);
	}
	return 0;
	
}

void powerset(int pos, int* val, int* sol, int n, int* minimo, int* bestsol)
{

	int i;
	if (pos >= n)
	{
		check(sol,val, n, minimo, bestsol);
		return;
	}
	sol[pos] = 0;
	powerset(pos + 1, val, sol, n, minimo, bestsol);
	sol[pos] = 1;
	powerset(pos + 1, val, sol, n, minimo, bestsol);
	
}
void check(int* sol,int *val, int n, int *minimo, int* bestsol)
{
	int flag = 0;
	int count = 0;
	int prev;
	int i,j;
	if (sol[n - 1] == 0)
		return;
	for (i = 0 ;i <n-1; i=i+j)
	{
		prev = i;
		if(sol[prev]==1)
			for (j = i + 1; j < n; j++)
			{
				if (sol[j] == 1)
				{
					if (prev + val[prev] >= j)
					{
						count++;
						if (j == n - 1)
						{
							flag = 1;
							break;
						}
						break;
					}
				}
			}
		if (flag == 1)
			break;
	}
	if (flag == 1)
	{
		if (count <= *minimo)
		{
			*minimo = count;
			for (i = 0; i < n; i++)
			{
				bestsol[i] = sol[i];
			}
		}
	
	}
	return;
}
