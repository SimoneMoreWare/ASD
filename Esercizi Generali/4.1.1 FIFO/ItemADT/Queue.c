#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "Queue.h"



struct queue {
    Item *b;
    int testa, coda;
    int n_el;
    int size;
};

int QUEUEnum(Q q) {
    if (q == NULL) return 0;
    return q->n_el;
}

Q QUEUEinit(int size) {
    Q q = (Q)malloc(sizeof(*q));
    if (q == NULL) {
        printf("Errore di allocazione di memoria\n");
        return NULL;
    }
    q->testa = q->coda = q->n_el = 0;
    q->size = size;
    q->b = (Item *) malloc(size * sizeof(Item));
    if (q->b == NULL) return NULL;
    return q;
}

void QUEUEfree(Q q) {
    int i, j;

    if (q == NULL)
        return;

    for(i=q->testa, j=0 ; j<q->n_el ; j++, i = (i+1) % q->size) {
        ITEMfree(q->b[i]);
    }
    free(q->b);
    free(q);
}

int QUEUEput(Q q, Item dato)
{
    if (QUEUEfull(q))
        return 1;

    if (q->n_el > 0)
        q->coda = (q->coda +1) % q->size;
    q->b[q->coda] = dato;
    q->n_el++;
    return 0;
}

int QUEUEget(Q q, Item *d)
{
    if (QUEUEempty(q))
        return 1;

    *d = q->b[q->testa];
    q->n_el--;
    if (q->n_el > 0) q->testa = (q->testa +1) % q->size;
    return 0;
}

void QUEUEshow(FILE *fp, Q q)
{
    int i, j;
    if (q == NULL || q->n_el == 0)
        return;

    for(i=q->testa, j=0; j<q->n_el ; j++, i=(i+1)%q->size) {
        ITEMstore(fp, q->b[i]);
    }
}

Q QUEUEscan(FILE *fp, int size)
{
    Item dato;
    Q q = QUEUEinit(size);
    if (q == NULL)
        return NULL;

    while (ITEMscan(fp, &dato) != 1 && q->n_el < q->size) {
        QUEUEput(q, dato);
    }
    return q;
}

int QUEUEempty(Q q)
{
    if (q == NULL || q->n_el == 0)
        return 1;
    else
        return 0;
}

int QUEUEfull(Q q)
{
    if (q == NULL || q->n_el == q->size)
        return 1;
    else
        return 0;
}

