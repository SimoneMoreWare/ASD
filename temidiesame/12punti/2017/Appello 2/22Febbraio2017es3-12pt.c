#include <stdio.h>
#include <stdlib.h>

#define N 5
#define K 2

int** matriceUni(int n);
void trovaInsieme(int** matriceDelleDipendenze, int n, int k);

int main(int argc, char **argv){
	int **matriceDelleDipendenze = matriceUni(N);
	
	//Solo per N >= 5, impongo che 1, 3, e 4 siano non separabili
	matriceDelleDipendenze[1][3] = 0;
	matriceDelleDipendenze[1][4] = 0;
	matriceDelleDipendenze[3][1] = 0;
	matriceDelleDipendenze[3][4] = 0;
	matriceDelleDipendenze[4][1] = 0;
	matriceDelleDipendenze[4][3] = 0;
	
	//Ovviamente è tutto riscrivibile per utilizzare massimo N²/2 operazioni ma non ho voglia
	
	printf("Cerco le soluzioni compatibil per partizionare l'insieme di 2 elementi in %d parti con almeno %d elementi nel secondo insieme.\n",
				N, K);
	trovaInsieme(matriceDelleDipendenze, N, K);
	
	return 420;
}

int soluzioneCompatibile(int* insieme2, int** matriceDelleDipendenze, int n){
	int i, j;
	
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			if (insieme2[i]) if (!insieme2[j]) if (!matriceDelleDipendenze[i][j]) return 0;
	
	return 1;
}

void disposizioni_semplici(int pos, int* insieme2, int** matriceDelleDipendenze, int n, int k, int attuale){
	int i;
	if (pos >= n){
		if (attuale >= k){
			if(soluzioneCompatibile(insieme2, matriceDelleDipendenze, n)){
				printf("Trovata una soluzione compatibile.\n");
				printf("Insieme I: ");
				for(i=0; i<n; i++) if (!insieme2[i]) printf("%d ", i);
				printf("\nInsieme II: ");
				for(i=0; i<n; i++) if (insieme2[i]) printf("%d ", i);
				printf("\n");
			}
		}
		return;
	}
	insieme2[pos] = 1;
	disposizioni_semplici(pos+1, insieme2, matriceDelleDipendenze, n, k, attuale+1);
	insieme2[pos] = 0;
	disposizioni_semplici(pos+1, insieme2, matriceDelleDipendenze, n, k, attuale);
	
	
}

void trovaInsieme(int** matriceDelleDipendenze, int n, int k){
	int* insieme2 = calloc(n, sizeof(int));
	disposizioni_semplici(0, insieme2, matriceDelleDipendenze, n, k, 0);
	free(insieme2);
}

int** matriceUni(int n){
	int i, j, **mat;
	mat = malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
		mat[i] = malloc(n*sizeof(int));
		for(j=0; j<n; j++)
			mat[i][j] = 1;
	}
	
	return mat;
}
