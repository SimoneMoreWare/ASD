#ifndef PRODOTTO_H_INCLUDED
#define PRODOTTO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 11
#define MAX 256

typedef struct{
   char id[MAXC], nome[MAX], categoria[MAXC];
   float prezzo;
   int disponibilita;
}Prodotto;

Prodotto PRODOTTOcrea(char *id, char *nome, char *categoria, float prezzo, int disp);
void PRODOTTOsetDisponibilita(Prodotto *p, int disp);
void PRODOTTOprint(Prodotto p, FILE *f);

#endif // PRODOTTO_H_INCLUDED
