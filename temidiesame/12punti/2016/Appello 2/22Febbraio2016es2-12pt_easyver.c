/*
Sia data una lista non ordinata di interi e un valore intero inteso come soglia. Si scriva una funzione C che divida la lista in
2 : nella prima lista compaiono gli elementi della lista originaria minori della soglia, nella seconda quelli maggiori o uguali
alla soglia. Sia mantenuto l’ordine relativo della lista originaria nelle 2 liste così create. Si noti che NON si può far
riferimento a funzioni di libreria sulle liste. Si usi un ADT di I categoria per le liste con una struct wrapper di tipo
lista_t. La funzione C sia compatibile con la chiamata effettuata dal seguente frammento del main:
lista_t *L0, *L1, *L2;
…
// acquisizione della lista L0
…
L1 = split_list(n, L0, &L2);
La funzione riceve come parametro la lista originale L0, ritorna la prima lista L1 e, by reference, la seconda L2.
Esempio: se la lista L0 in ingresso contiene i valori 7, 8, 25, 2, 9, -5, 10, 37 e la soglia è n=18, la prima lista L1 dovrà
contenere 7, 8, 2, 9, -5, 10 e la seconda L2 25,37.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elem_t* elem;
struct elem_t
{
	int valor;
	elem next;
};

typedef struct list
{
	elem head;
	elem tail;

}list_t;

list_t* splitlist(int n, list_t* l0, list_t** l2);
void addelem(list_t* l0, int valor);



int main()
{
	list_t* l0, * l1, * l2;
	l0 = calloc(1, sizeof(*l0));
	l0->head = NULL;
	l0->tail = NULL;
	l2 = calloc(1, sizeof(*l2));
	l2->head = l2->tail = NULL;
	addelem(l0,7);
	addelem(l0,8);
	addelem(l0,25 );
	addelem(l0,2 );
	addelem(l0,9 );
	addelem(l0,-5 );
	addelem(l0,10 );
	addelem(l0,37 );
	l1 = splitlist(18, l0, &l2);
	elem x;
	printf("lista 1 : ");
	for (x = l1->head; x != NULL; x = x->next)
	{
		printf("%d ", x->valor);
	}
	printf("\n");
	printf("lista 2: ");
	for (x = l2->head; x != NULL; x = x->next)
	{
		printf("%d ", x->valor);
	}
	return 0;


}
void addelem(list_t* l0, int valor)
{
	elem x = calloc(1, sizeof(*x));
	elem p;
	x->valor = valor;
	x->next = NULL;
	if (l0->head == NULL && l0->tail == NULL)
	{
		l0->head = l0->tail = x;
	}
	else
	{
		p = l0->tail;
		p->next = x;
		l0->tail = x;
	}
}

list_t* splitlist(int n, list_t* l0, list_t** l2)
{
	list_t* l1 = calloc(1, sizeof(*l1));
	l1->head = l1->tail = NULL;
	elem x;
	for (x = l0->head; x != NULL; x = x->next)
	{
		if (x->valor < 18)
		{
			addelem(l1, x->valor);
		}
		else
		{
			addelem(*l2, x->valor);
		}
	}
	return l1;
}
