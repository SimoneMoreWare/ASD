#include <stdio.h>
#include <stdlib.h>

int birthday(int* vet, int n, int m, int k);

int main(int argc, char **argv)
{
	int *vet1, *vet2, result;
	vet1 = malloc(5*sizeof(int));
		vet1[0] = 2;
		vet1[1] = 1;
		vet1[2] = 1;
		vet1[3] = 4;
		vet1[4] = 3;
	vet2 = malloc(6*sizeof(int));
		vet2[0] = 1;
		vet2[1] = 2;
		vet2[2] = 3;
		vet2[3] = 1;
		vet2[4] = 2;
		vet2[5] = 3;
	result = birthday(vet1, 5, 4, 3);
	printf("Elaborate %d combinazioni\n", result);
	result = birthday(vet2, 6, 3, 2);
	printf("Elaborate %d combinazioni\n", result);
	return 420;
		
}

int kGeneri(int* vet, int* libriScelti, int k, int m){
	int* generiScelti = calloc(m, sizeof(int)), i;
	for(i=0; i<k; i++)
		generiScelti[vet[libriScelti[i]]-1]++;
	for(i=0; i< m; i++) if (generiScelti[i] > 1) return 0;
	return 1;
}

void combinazioni_semplici(int pos, int start, int* libri, int* libriScelti, int* nScelte, int n, int k, int m){
	int i;
	if (pos >= k){
		if(kGeneri(libri, libriScelti, k, m)){
			(*nScelte)++;
			printf("(");
			for(i=0; i<k; i++) printf("%d ", libriScelti[i]);
			printf(")\n");
		}
		return;
	}
	for(i=start; i<n; i++){
		libriScelti[pos] = i;
		combinazioni_semplici(pos+1, i+1, libri, libriScelti, nScelte, n, m, k);
	}
}

int birthday(int* vet, int n, int m, int k){
	int* libriScelti = malloc(k*sizeof(int)), nScelte = 0;
	combinazioni_semplici(0, 0, vet, libriScelti, &nScelte, n, m, k);
	free(libriScelti);
	return nScelte;
}
