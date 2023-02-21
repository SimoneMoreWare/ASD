delle sottosequenze STRETTAMENTE CRESCENTI di X a lunghezza massima e restituisca come risultato la
sua lunghezza k:
int maxSubSeq(int *X, int N, int *Y);
Esempio: se X = 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15, le sottosequenze strettamente crescenti Y di X a
lunghezza massima (k = 6) sono:
0, 2, 6, 9, 11, 15
0, 4, 6, 9, 11, 15
0, 2, 6, 9, 13, 15
0, 4, 6, 9, 13, 15

*/

#include <stdio.h>
#include <stdlib.h>

#define N 16

int maxsub(int* X, int n);
void powerset(int pos, int* val, int* sol, int k,int *lun);
int check(int* sol,int *val, int k,int* ok);

int main()
{
	int X[N] = { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 };
	int k = maxsub(X, N);
	printf("%d", k);

}

int maxsub(int* X, int n)
{
	int* sol;
	int i;
	int ok = 0;
	int lun = 0;
	sol = calloc(N, sizeof(int));
	powerset(0, X, sol, N, &lun);
	return lun;
}

void powerset(int pos, int* val, int* sol, int k,int *lun)
{
	int i,ok,z;
	if (pos >= k)
	{
		ok = 0;
		z= check(sol, val, k, &ok);
		if (ok != 0)
		{
			if (z > * lun)
			{
				*lun = z;
			}
		}
		return;
	}
	sol[pos] = 0;
	powerset(pos + 1, val, sol, k,lun);
	sol[pos] = 1;
	powerset(pos + 1, val, sol, k,lun);
}

int check(int* sol,int *val, int k, int* ok)
{
	int* vet;
	int i,j=0,count=0;
	for (i = 0; i < k; i++)
	{
		if (sol[i] != 0)
			count++;
	}
	if (count == 0||count==1)
		return 0;
	*ok = 1;
	vet = malloc(count * sizeof(int));
	for (i = 0; i < k; i++)
	{
		if (sol[i] != 0)
		{
			vet[j++] = val[i];
		}
	}
	for (i = 1; i < count; i++)
	{
		if (vet[i] < vet[i - 1])
		{
			*ok = 0;
			break;
		}
	}
	if (*ok == 0)
		return 0;
	else
		return count;

}
