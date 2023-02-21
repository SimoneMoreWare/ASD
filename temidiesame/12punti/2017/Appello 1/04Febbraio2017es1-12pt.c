#include <stdio.h>
#include <stdlib.h>

#define N 5

void sommaCornici(int **mat, int n, int **vet);


int main(int argc, char **argv)
{
	int i, j, *vet;
	
	int** mat = malloc(N*sizeof(int*));
	for(i=0; i<N; i++) { 
		mat[i] = malloc(N*sizeof(int));
		for(j=0; j<N; j++) mat[i][j] = rand() % 10;
	}
		
	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
		
	printf("\n\n");
	
	sommaCornici(mat, N, &vet);
}

void sommaCornici(int **mat, int n, int **vet){
	int nAlloc = 0, n2 = n, i, k;
	while(n2 > 0) { nAlloc++; n2 -= 2; }
	(*vet) = calloc(nAlloc, sizeof(int));
	
	n2 = 0;
	k = 0;
	i = 0;
	
	for(k=0; k < nAlloc; k++){
		for(i=k; i<n-k; i++) (*vet)[k] += mat[k][i];
		for(i=k+1; i<n-k; i++) (*vet)[k] += mat[i][n-k-1];
		for(i=n-k-2; i>=k; i--) (*vet)[k] += mat[n-k-1][i];
		for(i=n-k-2; i>k; i--)  (*vet)[k] += mat[i][k];
	}
	
	for(i=0; i<nAlloc; i++)
		printf("Corona %d : %d\n", i+1, (*vet)[i]);
}