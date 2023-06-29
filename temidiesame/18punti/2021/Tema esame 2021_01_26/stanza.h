#ifndef STANZA_H_INCLUDED
#define STANZA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define CAR 200

typedef struct{
	int V, O, livello;
      char nome[CAR];
}Stanza;

Stanza STANZAread(FILE *f);
char* STANZAgetNome(Stanza *s);
void STANZAprint(Stanza s, FILE *f);


#endif // STANZA_H_INCLUDED
