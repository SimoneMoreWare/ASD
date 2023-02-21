#ifndef ESERCIZI_H_DEFINED
#define ESERCIZI_H_DEFINED

#include <stdio.h>

#define LEN 50

typedef struct esercizio_s {
  char *nomeEs;
  char *tipoEs;
  char *catEs;
} esercizio_t;

typedef struct esercizi_s {
  int nEsercizi;
  int dimVett;
  esercizio_t *ve;
} tabEser;

typedef struct eserPiano_s {
  int set, rip;
  esercizio_t *es;
} eserPiano_t;

typedef struct nodoPiano_s *linkPiano;
typedef struct nodoPiano_s {
  eserPiano_t p;
  linkPiano next;
} nodoPiano_t;

void stampaEsercizi(tabEser *esercizi, char* file); /* char* file = NULL per stampare sullo stdout */
void caricaEsercizi(tabEser *esercizi);
void caricaPiano(char *codice, linkPiano *head, linkPiano *tail, tabEser *esercizi);
void stampaPiano(FILE *fp, linkPiano p);
void aggiornaEsercizioInPiano(linkPiano *head, linkPiano *tail, tabEser *esercizi);
void freePiano(linkPiano p);
void liberaEsercizi(tabEser *esercizi);

#endif
