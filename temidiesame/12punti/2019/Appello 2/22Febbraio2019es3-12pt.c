#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define N 9

void subseq(int v[], int n);
int subseq_r(int *v, int n, int k, int *y, int l, int *yMax, int lMax);

int main(int argc, char *argv[]) {
	int V[N] = {8, 9, 6, 4, 5, 7, 3, 2, 4};
	//int V[N] = {4, 11, 3, 8, 5, 6, 2, 10, 1};
	
	subseq(V, N);
	return 0;
}

void subseq(int *v, int n)
{
	int *y, *yMax;
	int i, l, lMax;
	
	y = (int *)malloc(n*sizeof(int));
	yMax = (int *)malloc(n*sizeof(int));

	l = lMax = 0;
	lMax = subseq_r(v, n, 0, y, l, yMax, lMax);	

	printf("Sotto-sequenza di lunghezza massima (%d): ", lMax);
	for (i=0; i<lMax; i++) {
		printf("%d ", yMax[i]);
	}
	printf("\n");
	
	free(y);
	free(yMax);
}

int subseq_r(int *v, int n, int k, int *y, int l, int *yMax, int lMax)
{
	int i;
	
	if (lMax < l) {
		for (i=0; i<l; i++) {
			yMax[i] = y[i];
		}
		lMax = l;
	}
	
	if (l == 0) {
		/* inizio una nuova possibile sequenza */
		for (i=0; i<n; i++) {
			y[l] = v[i];
			lMax = subseq_r(v, n, i+1, y, l+1, yMax, lMax);
		}
		return lMax;
	}

	if (l % 2) {
		/* ultimo valore inserito di indice PARI: verifico se se ne possono inserire altri di valore maggiore */
		for (i=k; i<n; i++) {
			if (v[i] > y[l-1]) {
				y[l] = v[i];
				lMax = subseq_r(v, n, i+1, y, l+1, yMax, lMax);
			}
		}
	} else {
		/* ultimo valore inserito di indice DISPARI: verifico se se ne possono inserire altri di valore minore */
		for (i=k; i<n; i++) {
			if (v[i] < y[l-1]) {
				y[l] = v[i];
				lMax = subseq_r(v, n, i+1, y, l+1, yMax, lMax);
			}
		}
	}
	return lMax;
}
