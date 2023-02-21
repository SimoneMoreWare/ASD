/*
Una matrice si dice "sparsa" quando la maggior parte delle caselle contiene un valore nullo. Nel caso di una
matrice sparsa, può' risultare conveniente l'utilizzo di una struttura dati che allochi dinamicamente memoria
per le sole caselle non nulle.
Si realizzi in C, per una matrice sparsa di numeri (tipo float), gestita come ADT di prima categoria, la
funzione di prototipo
MATRwrite (matr_t *M, int r, int c, float val);
che inserisca alla riga r e alla colonna c il valore val. Il tipo matr_t è una struct che, oltre a contenere, come
interi, le due dimensioni della matrice (NR, numero di righe, e NC, numero di colonne) punta a un vettore (di
dimensione NR) di puntatori a righe, ognuna realizzata mediante una lista, contenente gli elementi non nulli
della riga corrispondente). Si definisca matr_t, si definisca poi il tipo struct usato per le liste e si scriva infine
la funzione MATRwrite.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct riga_s* link;

struct riga_s
{
	int col;
	float val;
	link next;
};

typedef struct matr
{
	int quant;
	link head;
}matr_t;

void matrwrite(matr_t* M, int r, int c, float val);
int** matread(int* R, int* C,char *filename);
matr_t* matrinit(int R);
link create(float val, int c,link next);
void printmatrix(matr_t* M, int R, int C);

int main()
{
	int i, j;
	int** matr;
	int R, C;
	matr_t* M;
	matr = matread(&R, &C, "matr.txt");
	M = matrinit(R);
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			if (matr[i][j] != 0)
				matrwrite(M, i, j, matr[i][j]);
		}
	}
	printmatrix(M, R, C);
	return 0;

}

int** matread(int* R, int* C, char* filename)
{
	int i,j;
	int** matr;
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("apertura fallita\n");
		exit(0);
	}
	fscanf(fp, "%d %d", R, C);
	matr = malloc((*R) * sizeof(int*));
	for (i = 0; i < *R; i++)
	{
		matr[i] = malloc(*C * sizeof(int));
		for (j = 0; j < *C; j++)
		{
			fscanf(fp, "%d", &matr[i][j]);
		}
	}
	return matr;
}

matr_t* matrinit(int R)
{
	int i;
	matr_t* M;
	M = malloc(R * sizeof(matr_t));
	for (i = 0; i < R; i++)
	{
		M[i].quant = 0;
		M[i].head = NULL;
	}
	return M;
}

void matrwrite(matr_t* M, int r, int c, float val)
{
	link x = create(val, c, NULL);
	link p;
	if (M[r].head == NULL)
	{
		M[r].head = x;
	}
	else
	{
		p = M[r].head;
		M[r].head = x;
		M[r].head->next = p;
		
	}
}

link create(float val, int c, link next)
{
	link x = calloc(1, sizeof(*x));
	x->col = c;
	x->val = val;
	x->next = next;
	return x;
}

void printmatrix(matr_t* M, int R, int C)
{
	link x,p;
	int flag = 0;
	int i,j;
	int val;
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			for (x = M[i].head;x!=NULL; x = x->next)
			{
				if (x->col == j)
				{
					flag = 1;
					val = x->val;
					break;
				}
			
			}
			if (flag == 1)
			{
				printf("%d ", val);

			}
			else
			{
				printf("0 ");
			}
			flag = 0;
		}
		printf("\n");
		flag = 0;
	}
}
