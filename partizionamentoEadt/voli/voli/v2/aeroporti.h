#ifndef AERO_H
#define AERO_H

#define M1 40
#define M2 8

typedef struct aeroporto_s *linkAeroporto,  aeroporto_t;

struct aeroporto_s {
  char *nomeAeroporto;
  char *nomeCitta;
  char codice[M2];
  linkAeroporto next;
};

typedef struct {
  linkAeroporto head;
  linkAeroporto tail;
} aeroporti_t;

aeroporti_t *allocaAeroporti ();
void liberaAeroporti (aeroporti_t *ap);
void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti);
aeroporti_t *leggiAeroporti (char *nomeFile);
aeroporto_t *cercaAeroportoC(aeroporti_t *aeroporti, char *codice);

#endif
