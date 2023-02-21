/*
Sia data una matrice sparsa di float realizzata mediante un ADT (tipo matr_t ) di prima categoria, che
internamente gestisce i dati mediante una lista di liste. Si ricordi che una matrice si dice sparsa se viene
realizzata con una struttura dati che alloca memoria per i soli dati non nulli. La lista di liste è così composta:
 una lista di primo livello contiene un elemento per ogni riga della matrice contenente almeno un dato non
nullo,
 ad ogni elemento di questa prima lista corrisponde una sotto-lista, contenente un elemento per ogni dato
non nullo della riga.
Al tipo matr_t corrisponde una struct wrapper contenente le dimensioni della matrice e il puntatore al
primo elemento della lista di righe.
Si scriva la funzione MatrWrite, di prototipo
void MatrWrite (matr_t *M, float d, int r, int c);
che scrive nella matrice il dato d nella casella di indici r, c. Sono possibili quattro casi:
 d != 0.0 e la matrice sparsa non contiene dati in riga r e colonna c. Il dato va aggiunto
 d != 0.0 e la matrice sparsa contiene già un dato in riga r e colonna c. Il vecchio dato viene sostituito
da quello nuovo
 d == 0.0 e la matrice sparsa non contiene dati in riga r e colonna c. Non si fa nulla
 d == 0.0 e la matrice sparsa contiene un dato in riga r e colonna c. Il dato va rimosso.
Si noti che NON si può far riferimento a funzioni di libreria sulle liste. Si richiede la realizzazione della
funzione, nonché la definizione dei tipi struct (compreso matr_t) utilizzati.


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem
{
	float val;
	int c;
	struct elem* next;
}elem;

typedef struct matr
{
	elem *elemento;
	struct matr_t* prossimo;
	int r;
}matr_t;


float** leggimatr(char* filename,int *R, int *C);
void matrwrite(matr_t* M, float d, int r, int c);
matr_t* matrinit(int R);
void addmatr(matr_t** M, int R);
void add(matr_t* M, int r ,int c,float val);
int check(matr_t* M, int r, int c,float val);
void change(matr_t* M, int r, int c);
void printmatrix(matr_t* M, int r, int c);

int main()
{
	int R, C;
	float** matr = leggimatr("matr.txt",&R,&C);
	int i, j;
	matr_t* M = matrinit(R);
	matr_t* p;
	for (i = 0; i < R; i++)
	{
		for (j = 0; j < C; j++)
		{
			matrwrite(M, matr[i][j], i, j);
		}
	}
	printmatrix(M, R, C);

}

float** leggimatr(char* filename, int* R, int* C)
{
	int i,j;
	FILE* fp;
	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(0);
	fscanf(fp, "%d %d", R, C);
	float** matr;
	matr = calloc(*R, sizeof(float*));
	for (i = 0; i < *R; i++)
		matr[i] = calloc(*C, sizeof(float));
	for (i = 0; i < *R; i++)
	{
		for (j = 0; j < *C; j++)
		{
			fscanf(fp, "%f", &matr[i][j]);

		}
	}
	return matr;
	
}
matr_t* matrinit(int R)
{
	int i;
	matr_t* M = calloc(1, sizeof(*M));
	M->r = R - 1;
	M->elemento = NULL;
	M->prossimo = NULL;
	R = R - 2;
	for (i = R; i >= 0; i--)
	{
		addmatr(&M, i);
	}
	return M;
}

void addmatr(matr_t** M, int R)
{
	matr_t* x, *p;
	x = calloc(1, sizeof(*x));
	x->elemento = NULL;
	x->prossimo = NULL;
	x->r = R;
	p = *M;
	x->prossimo = *M;
	*M = x;
}

void matrwrite(matr_t* M, float d, int r, int c)
{
	if (d != 0.0)
	{
		if (check(M, r, c,d))
		{
			add(M, r, c, d);
		}
		else
		{
			change(M,r,c);
		}
	}
}

int check(matr_t* M, int r, int c, float val)
{
	int check = 1;
	matr_t* p;
	elem* e;
	for (p = M; p != NULL; p = p->prossimo)
	{
		if (p->r == r)
		{
			if (p->elemento == NULL)
				return 1;
			for (e = p->elemento;e != NULL;e = e->next)
			{
				if (e->c == c)
					p->elemento->val = val;
			}
			return 1;
		}
	}
}

void add(matr_t* M, int r, int c, float val)
{
	matr_t* p;
	elem* x,*z;
	x = calloc(1, sizeof(*x));
	x->c = c;
	x->next = NULL;
	x->val = val;
	for (p = M; p != NULL; p = p->prossimo)
	{
		if (p->r == r)
		{
			if (p->elemento == NULL)
			{
				p->elemento = x;
				return;
			}
			else
			{
				z = p->elemento;
				x->next = z;
				p->elemento = x;

			}
		}
	}
}
void change(matr_t* M, int r, int c)
{
	matr_t* p;
	elem* x, * z,*y;
	for (p = M; p != NULL; p = p->prossimo)
	{
		if (p->r == r)
		{
			if (p->elemento == NULL)
				return;
			for (x = p->elemento,z=NULL; x != NULL; z=x,x = x->next)
			{
				if (x->c == c)
				{
					y = x->next;
					z->next = y;
					free(x);
					x = y;
				}
				return;
			}
		}
	}
}
void printmatrix(matr_t* M, int r, int c)
{
	matr_t* p;
	elem* e;
	float** matr;
	int i, j;
	matr = calloc(r, sizeof(float*));
	for (i = 0; i < r; i++)
		matr[i] = calloc(c, sizeof(float));
	
	for (p = M; p != NULL; p = p->prossimo)
	{
		for (e = p->elemento; e != NULL; e = e->next)
		{
			matr[p->r][e->c] = e->val;
		}
	}
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			printf("%f ", matr[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < r; i++)
		free(matr[i]);
	free(matr);
	return;
}
