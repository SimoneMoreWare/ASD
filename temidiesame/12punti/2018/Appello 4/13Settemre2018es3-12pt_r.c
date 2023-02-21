/*
Un vettore paste di n struct descrive le tipologie e le disponibilità dei pasticcini realizzati da un
laboratorio di pasticceria. Ogni struct consta di 3 campi interi non negativi:
 codice identifica la tipologia di pasticcino (ad esempio 3 bigné, 5 crostatina, etc.)
 peso indica il peso in grammi di ogni pasticcino
 quantita indica il numero di pasticcini di quella tipologia disponibili.
Si scriva un programma C che, ricevuti come parametro il vettore, la sua lunghezza e un intero che
rappresenta il peso del vassoio di pasticcini da comporre, calcoli l'insieme di pasticcini il cui peso si
avvicini il più possibile (al più eguagli) al peso richiesto, tenendo conto delle disponibilità di ogni
tipologia. Si proceda quindi a stampare tale insieme, specificando per ogni tipologia di pasticcini la sua
cardinalità, ed il peso finale del vassoio. Nel caso di più soluzioni equivalenti è sufficiente stamparne
una. Si supponga inoltre che l'utente non abbia alcuna preferenza sulla tipologia di pasticcini
selezionati.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20

typedef struct elem
{
	char* codice;
	int q;
	int p;
}pasticino;

pasticino* readfromfile(char* nomefile, int* dim);
void elabora(pasticino* vet, int dim, int peso);
void caricavet(int* vet,int ind, int start, int dim);
void powerset(int pos, int* val, pasticino* vet,int dim, int peso, int *max, int* sol, int* bestsol, int k);
int check(pasticino* vet, int dim, int k, int* sol,int *val);
int main()
{
	int i,peso;
	int dim;
	pasticino* vet;
	vet = readfromfile("past.txt", &dim);
	for (i = 0; i < dim; i++)
	{
		printf("%s %d %d \n", vet[i].codice, vet[i].p, vet[i].q);
	}
	int max = 0;
	printf("inserisci il peso : ");
	scanf("%d", &peso);
	elabora(vet, dim, peso);

}
/* past.txt:
5
croissant 50 5
brioche 30 5
crostatina 80 5
bigne 15 5
mousse 20 5
*/
pasticino* readfromfile(char* nomefile, int* dim)
{
	char cod[N];
	pasticino* vet;
	int i;
	FILE* fp;
	fp = fopen(nomefile, "r");
	if (fp == NULL)
	{
		printf("apertura file fallito\n");
		exit(0);
	}
	fscanf(fp, "%d", dim);
	vet = calloc(*dim, sizeof(pasticino));
	for (i = 0; i < *dim; i++)
	{
		fscanf(fp,"%s %d %d", cod, &vet[i].p, &vet[i].q);
		vet[i].codice = _strdup(cod);
	}
	return vet;
}
void elabora(pasticino* vet, int dim, int peso)
{
	int max = 0;
	int* val;
	int i,j,count=0;
	int start = 0;
	int* sol,*bestsol;
	for (i = 0; i < dim; i++)
	{
		count = count + vet[i].q;
	}
	val = calloc(count, sizeof(int));
	for (i = 0; i < dim;i++)
	{
		j = vet[i].q;
		caricavet(val,i, start, j);
		start = start + j;
	}
	sol = calloc(count, sizeof(int));
	bestsol = calloc(count, sizeof(int));
	powerset(0, val, vet, dim, peso, &max, sol, bestsol, count);
	printf("il vasoio è composto da :\n");
	for (i = 0; i < count; i++)
	{
		if (bestsol[i] != 0)
		{
			printf("%s\n", vet[val[i]].codice);
		}
	}
	printf("il peso è: %d ", max);
	
}
void caricavet(int* vet, int ind, int start, int dim)
{
	int i;
	for (i = start; i < start + dim; i++)
	{
		vet[i] = ind;
	}
	return;
}
void powerset(int pos, int* val, pasticino* vet, int dim, int peso, int* max, int* sol, int* bestsol, int k)
{
	int maxloc,i;
	if (pos >= k)
	{
		maxloc = check(vet, dim, k, sol,val);
		if (maxloc > * max && maxloc <= peso)
		{
			*max = maxloc;
			for (i = 0; i < k; i++)
			{
				bestsol[i] = sol[i];
			}
		}
		return;
	}
	sol[pos] = 0;
	powerset(pos + 1, val, vet, dim, peso, max, sol, bestsol, k);
	sol[pos] = 1;
	powerset(pos + 1, val, vet, dim, peso, max, sol, bestsol, k);
}

int check(pasticino* vet, int dim, int k, int* sol,int *val)
{
	int i;
	int peso=0;
	for (i = 0; i < k; i++)
	{
		if (sol[i] != 0)
		{
			peso = peso + vet[val[i]].p;
		}
	}
	return peso;
}
