#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 5

int tutteAccese(int controls[N][M], int* soluzione, int n, int m);
void disposizioni_semplici(int pos, int n, int m, int mark[N], int controls[N][M], int* minimo, int soluzione[N]);

int main(int argc, char **argv)
{
	int controls[N][M] =
	{
		{1, 1, 0, 0, 1},
		{1, 0, 1, 0, 0},
		{0, 1, 1, 1, 0},
		{1, 0, 0, 1, 0}
	},
		mark[N] = {0},
		minimo = N+1,
		soluzione[N] = {0};
	
	disposizioni_semplici(0, N, M, mark, controls, &minimo, soluzione);
	
	printf("La soluzione col minor numero di interruttori (%d) e': ", minimo);
	for(int i=0; i<N; i++) if (soluzione[i]) printf("%d ", i);
	printf("\n");
	
	return 420;
}

void disposizioni_semplici(int pos, int n, int m, int mark[N], int controls[N][M], int* minimo, int soluzione[N]){
	int numeroInterruttori, i;
	if (pos >= n){
		if (tutteAccese(controls, mark, n, m)){
			numeroInterruttori = 0;
			for(i=0; i<n; i++) if (mark[i]) numeroInterruttori++;
			if (numeroInterruttori < *minimo){
				*minimo = numeroInterruttori;
				for(i=0; i<n; i++) soluzione[i] = mark[i];
			}
		}
		return;
	}
	mark[pos] = 0;
	disposizioni_semplici(pos+1, n, m, mark, controls, minimo, soluzione);
	mark[pos] = 1;
	disposizioni_semplici(pos+1, n, m, mark, controls, minimo, soluzione);
}

int tutteAccese(int controls[N][M], int* soluzione, int n, int m){
	int i, j;
	int* candele = calloc(n, sizeof(int));
	for(i=0; i<n; i++)
		if (soluzione[i])
			for(j=0; j<m; j++)
				if(controls[i][j])
					candele[j] = !candele[j];
	for(i=0; i<n; i++)
		if(!candele[i]) { free(candele); return 0; }
	free(candele);
	return 1;
}
