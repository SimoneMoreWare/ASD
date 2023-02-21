#define M1 40
#define M2 8

typedef struct aeroporti_s aeroporti_t;
/* puntatore opaco a struct del modulo voli */
typedef struct voli_s voli_t;

int cercaAeroportoC(aeroporti_t *aeroporti, char *codice);
char *codiceAeroporto(aeroporti_t *aeroporti, int id);
void liberaAeroporti (aeroporti_t *ap);
void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti);
void generaPartenzeArrivi (aeroporti_t *aeroporti, voli_t *voli);
void scriviPartenzeArrivi (char *nomeFile, aeroporti_t *aeroporti, voli_t *voli);
aeroporti_t *allocaAeroporti (int max);
aeroporti_t *leggiAeroporti (char *nomeFile);

