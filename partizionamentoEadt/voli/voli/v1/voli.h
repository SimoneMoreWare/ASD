#ifndef VOLI_H
#define VOLI_H

#define M1 40
#define M2 8
#include "aeroporti.h"

typedef struct {
  int h, m;
} orario_t;

typedef struct volo_s {
  struct {
    aeroporto_t *citta;
    orario_t ora;
  } partenza, arrivo;
  char codiceVolo[M2];  
} volo_t;

typedef struct {
  volo_t *elenco;
  int nv, nmax;
} voli_t;

void liberaVoli (voli_t *vp);
void scriviVolo (FILE *f, volo_t *vp);
void scriviVoli (char *nomeFile, voli_t *voli);
voli_t *allocaVoli (int max);
voli_t *leggiVoli (char *nomeFile, aeroporti_t *aeroporti);
orario_t leggiOra (FILE *fp);

#endif
