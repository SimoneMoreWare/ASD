/* atleti.h */
#ifndef ATLETI_H
#define ATLETI_H
#include <stdio.h>
#include "esercizi.h"

typedef struct data_s{
  int giorno;
  int mese;
  int anno;
} data_t;

typedef struct atleta_s {
  char* codice;
  char* cognome;
  char* nome;
  int categoria;
  data_t data;
  int ore;
  linkPiano head, tail;
} atleta_t;

typedef struct nodoAtleta_s *linkAtleta;
typedef struct nodoAtleta_s {
  atleta_t a;
  linkAtleta next;
} nodoAtleta_t;

typedef struct atleti_s {
  int nAtleti;
  linkAtleta head, tail;
} tabAtleti;

typedef struct categoria_s {
  char* nome;
} categoria_t;

typedef struct categorie_s {
  int nCategorie;
  int dimVett;
  categoria_t *vc;
} categorie_t;

int comparaData(data_t d1, data_t d2);
int leggiAtleta(FILE *fp, atleta_t *a, categorie_t *categorie);
void stampaAnagrafica(tabAtleti *atleti, categorie_t *categorie, char* file); /*char* file = NULL per stampare sullo stdout */
void caricaAnagrafica(tabAtleti *atleti, categorie_t *categorie);
void parsificaData(char strData[], data_t *data);
void stampaAtleta(atleta_t *atleta, categorie_t *categorie, FILE *fp);
void stampaPerCategoria(tabAtleti *atleti, categorie_t *categorie);
void ricercaCognome(tabAtleti *atleti, categorie_t *categorie, char* cognome, int nCharConfronto);
int ricercaCodice(tabAtleti *atleti, char *codice, atleta_t *a);
int ricercaCodiceModifica(tabAtleti *atleti, char *codice, int nuoveOre);
int ricercaCodiceCaricaPiano(tabAtleti *atleti, tabEser *esercizi, char *codice);
int ricercaCodiceModificaPiano(tabAtleti *atleti, tabEser *esercizi, char *codice);
void elimina(tabAtleti *atleti, char* codice);
void aggiungi(tabAtleti *atleti, categorie_t *categorie);
void liberaAtleti(tabAtleti *atleti);
void liberaCategorie(categorie_t *categorie);

#endif
