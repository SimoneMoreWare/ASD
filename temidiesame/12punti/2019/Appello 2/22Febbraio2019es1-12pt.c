#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define N 7

int maxSomma(int v[], int *iMax, int *mMax);
int somma(int v[], int pos, int n);

int main(int argc, char *argv[]) {
	int V[N] = {-1, 2, 3, -6, 1, 3, 1};
	int i, mMax, iMax, sMax;

	sMax = maxSomma(V, &iMax, &mMax);
	printf("Sotto-vettore richiesto ");
	printf("(dimensione %d, somma %d): ", mMax, sMax);
	for (i=iMax; i<iMax+mMax; i++) {
		printf("%d ", V[i]);
	}
	printf("\n\n");
	system("pause");
	return 0;
}

int maxSomma(int v[], int *posMax, int *mMax)
{
	int i, iMax, s, sMax, dim, dimMax;

	sMax = INT_MIN;
	for (dim=1; dim<N; dim++) {
 		for (i=0; i<=N-dim; i++) {
 			s = somma(v, i, dim);
 			if (s > sMax) {
 				sMax = s;
 				iMax = i;
 				dimMax = dim;
			}
 			//printf("i=%d, d=%d -> s=%d (%d)\n", i, dim, s, sMax);
 		}
	}
	*posMax = iMax;
	*mMax = dimMax;
	return sMax;
}

int somma(int v[], int pos, int n)
{
	int i, s;

	s = 0;
	for (i=0; i<n; i++) {
		s += v[pos+i];
	}
	return s;
}
