#ifndef AERO_H
#define AERO_H

#define M1 40
#define M2 8

typedef struct {
  char *nomeAeroporto, nomeCitta;
  char codice[M2];
} aeroporto_t;

typedef struct {
  aeroporto_t *elenco;
  int na, nmax;
} aeroporti_t;

aeroporti_t *allocaAeroporti (int max);
void liberaAeroporti (aeroporti_t *ap);
void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti);
aeroporti_t *leggiAeroporti (char *nomeFile);
int cercaAeroportoC (aeroporti_t *aeroporti, char *codice);

#endif