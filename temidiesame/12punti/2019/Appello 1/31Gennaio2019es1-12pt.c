#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define N 4
#define M 3

int minmaxdiff(int **A, int n, int m);

int main(void) {
	int **A, i, j;
	int B[N][M] = {
					{15, 13,  7}, 
					{ 6, 18,  4}, 
					{11,  4, 12}, 
					{13,  9,  5}
				  };
	
	A = (int **)malloc(N*sizeof(int *));
	for (i=0; i<N; i++) {
		A[i] = (int *)malloc(M*sizeof(int));
		for (j=0; j<M; j++) {
			A[i][j] = B[i][j];
		}
	}
	
	j = minmaxdiff(A, N, M);
	printf("Colonna con differenza massima: %d\n", j);
	return 0;
}

int minmaxdiff(int **A, int n, int m)
{
	int i, j, jMax;
	int diff, diffMax;
	
	diffMax = 0;
	for (j=0; j<m; j++) {
		for (i=0; i<n-1; i++) {
			diff = abs(A[i][j]-A[i+1][j]);
			if (diff > diffMax) {
				diffMax = diff;
				jMax = j;
			}
		}
	}
	
	printf("Differenza massima: %d\n", diffMax);
	return jMax;
}
