/* typedef struct voli_s voli_t; gia' definito in aeroporti.h */

int numVoli(voli_t *voli);
voli_t *allocaVoli (int max);
void liberaVoli (voli_t *vp);
int greaterOra (voli_t *tabV, int id1, int id2, int partenza);
voli_t *leggiVoli (char *nomeFile, aeroporti_t *aeroporti);
void scriviVolo (FILE *f, aeroporti_t *aeroporti, voli_t *voli,     int id);
void scriviVoli (char *nomeFile, aeroporti_t *aeroporti, voli_t      *voli);
int voloAeroporto (voli_t *voli, int idVolo, int partenza);
