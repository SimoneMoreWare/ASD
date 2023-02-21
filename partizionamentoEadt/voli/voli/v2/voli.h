#ifndef VOLI_H
#define VOLI_H
#include "aeroporti.h"
#define M1 40
#define M2 8

typedef struct volo_s *linkVolo, volo_t;

typedef struct {
  int h, m;
} orario_t;

struct volo_s {
  struct {
    aeroporto_t *citta;
    orario_t ora;
  } partenza, arrivo;
  char codiceVolo[M2];  
  linkVolo next;
};

typedef struct {
  linkVolo head;
  linkVolo tail;
} voli_t;


void scriviVolo (FILE *f, volo_t *vp);
void scriviVoli (char *nomeFile, voli_t *voli);
void liberaVoli (voli_t *vp);
voli_t *allocaVoli ();
orario_t leggiOra (FILE *fp);
voli_t *leggiVoli (char *nomeFile, aeroporti_t *tabA);

#endif
