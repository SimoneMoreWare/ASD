#ifndef VOLI_H
#define VOLI_H

#include "aeroporti.h"

#define M1 40
#define M2 8

typedef struct {
  int h, m;
} orario_t;

typedef struct volo_s {
  struct {
    int idCitta; /* indice in tabella aeroporti */
    orario_t ora;
  } partenza, arrivo;
  char codiceVolo[M2];  
} volo_t;

typedef struct {
  volo_t *elenco;
  aeroporti_t *aeroporti;
  int nv, nmax;
} voli_t;

void liberaVoli (voli_t *vp);
void scriviVolo (FILE *f, voli_t *voli, int id);
void scriviVoli (char *nomeFile, voli_t *voli);
voli_t *allocaVoli (int max);
voli_t *leggiVoli (char *nomeFile, aeroporti_t *aeroporti);
orario_t leggiOra (FILE *fp);

#endif
