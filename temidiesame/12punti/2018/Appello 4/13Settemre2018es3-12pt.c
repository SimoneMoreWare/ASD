#include <stdio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define N 4
#define M 8

int taglia(int n, int m, int *lunghezza, int *prezzo, int *sol, int *best, int valore, int max, int k);

int main(void) 
{
    int lunghezza[M] = { 7, 4,  8, 1,  5, 2,  6, 3};
    int prezzo[M]    = {17, 9, 20, 1, 10, 5, 17, 8};
    int sol[M] = {0};
    int best[M] = {0};
    int i, max;
	
	max = taglia(N, M, lunghezza, prezzo, sol, best, 0, 0, 0);

	printf("Valore massimo = %d\n", max);
	printf("Tagli: (lunghezza totale = %d)\n", N);
	for (i=0; i<M; i++) {
		printf("- %d pezzi di lunghezza %d\n", best[i], lunghezza[i]);
	}		
	
	return 0;
}

int taglia(int n, int m, int *lunghezza, int *prezzo, int *sol, int *best, int valore, int max, int k)
{
	int i;
	
	if (k >= m) {
		return max;
	}
	
	if (n >= lunghezza[k]) {
		n -= lunghezza[k];
		sol[k]++;
		valore += prezzo[k];
		if (valore > max) {
			max = valore;
			for (i=0; i<m; i++) {
				best[i] = sol[i];
			}
		}
		max = taglia(n, m, lunghezza, prezzo, sol, best, valore, max, k);
		n += lunghezza[k];
		sol[k]--;
		valore -= prezzo[k];
	}
	max = taglia(n, m, lunghezza, prezzo, sol, best, valore, max, k+1);
	return max;	
}
