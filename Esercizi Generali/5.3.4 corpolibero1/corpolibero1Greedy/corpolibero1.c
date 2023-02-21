#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DBG 0
#define EX 8
#define CAT 3
#define MAX 256
#define ESIGENZA 2.50

typedef enum {NA, AA, AI} cat;

typedef struct elemento_ {
  char *nomeE;
  int diff;
  float punti;
  cat categoria;
} elemento;

typedef struct elementi_ {
  int NA, AA, AI, nEl;
  elemento *vet;
} elementi;

typedef struct soluzione_ {
  int sol[EX];
  float val;
  int diff;
  int ultimo;
} soluzione;

elementi *leggiFile(FILE *in) {
  int i, idCat;
  char tmp[MAX];
  elementi *wrapper = malloc(sizeof(elementi));
  if (wrapper == NULL)
    return NULL;

  fscanf(in, "%d %d %d\n", &wrapper->NA, &wrapper->AA, &wrapper->AI);
  wrapper->nEl = wrapper->NA + wrapper->AA + wrapper->AI;

  wrapper->vet = calloc(wrapper->nEl, sizeof(elemento));
  if (wrapper->vet == NULL) {
    free(wrapper);
    return NULL;
  }

  for(i=idCat=0; i<wrapper->nEl; i++) {
    fscanf(in, "%s %d %f", tmp, &wrapper->vet[i].diff, &wrapper->vet[i].punti);
    if (i==wrapper->NA || i==(wrapper->NA+wrapper->AA)) {
      /* nuova categoria */
	  idCat++;
	}
    wrapper->vet[i].categoria = idCat;
    wrapper->vet[i].nomeE = strdup(tmp);
    if (wrapper->vet[i].nomeE == NULL)
      return NULL;
  }
  return wrapper;
}

void stampaSol(elementi *e, soluzione *s, char *frase) {
  int i,s_i;
  printf("%s %.2f\n", frase==NULL?"":frase, s->val);
  for(i=0;i<EX;i++) {
    s_i = s->sol[i];
    printf("%-40s %4d %6.2f %4d\n", e->vet[s_i].nomeE, e->vet[s_i].diff,
           e->vet[s_i].punti, e->vet[s_i].categoria);
  }
  printf("\n");
}

void stampaElementi(elementi *e) {
  int i;
  for(i=0; i<e->nEl; i++) {
    if (i==e->NA || i==(e->NA+e->AA)) {
      /* nuova categoria: stampa separatore */
      printf("--\n");
    }
    printf("%-40s p = %6.2f d = %4d\n", e->vet[i].nomeE, e->vet[i].punti,e->vet[i].diff);
  }
}

int ElMaggiore(elemento *e1, elemento *e2) {
  return (e1->punti/e1->diff > e2->punti/e2->diff);
}

void ordinaGreedy(elementi *e) {
  int i, j;
  elemento tmp;

  for (i=1; i<e->nEl; i++) {
    tmp =  e->vet[i];
    for (j=i-1; j>=0 && ElMaggiore(&tmp,&(e->vet[j])); j--) {
      e->vet[j+1] = e->vet[j];
    }
    e->vet[j+1] = tmp;
  }
}

/* GREEDY SEMPLICE - ordina per punteggio relativo (punteggio/difficolta'.
Non tiene conto di altri criteri. Non garantisce la soluzione. */

void risolviGreedy(elementi *e, int maxCat[CAT], int maxSUM) {
  int i,j;
  soluzione sol;

  sol.val = 0.0;
  sol.diff = 0;

  ordinaGreedy(e);
  stampaElementi(e);

  for (i=j=0; i<e->nEl && j<EX; i++) {
    if ((e->vet[i].diff <= maxCat[e->vet[i].categoria]) &&
        (e->vet[i].diff <= (maxSUM - sol.diff))) {
      sol.sol[j++] = i;
      sol.val += e->vet[i].punti;
      sol.diff += e->vet[i].diff;
    }
  }

  if (j==EX) {
    stampaSol(e,&sol,"Soluzione greedy:");
  }
  else
    printf("Soluzione greedy non trovata\n");
}


/* MAIN */

int main(int argc, char **argv) {
  int i;
  int maxCat[CAT], maxSUM;
  FILE *in;
  elementi *e;
  if (argc != 6) {
    printf("Uso: %s file_elementi maxNA maxAA maxAI maxSUM", argv[0]);
    return -1;
  }
  maxSUM = atoi(argv[5]);
  in = fopen(argv[1], "r");

  e = leggiFile(in);
  if (e == NULL)
    return -1;
#if DBG
  stampaElementi(e);
#endif /* DBG */
  fclose(in);
  maxCat[NA] = atoi(argv[2]);
  maxCat[AA] = atoi(argv[3]);
  maxCat[AI] = atoi(argv[4]);
  maxSUM = atoi(argv[5]);

  printf("Algoritmo greedy: ordinamento per punteggio specifico senza ripetizioni\n");
  risolviGreedy(e, maxCat, maxSUM);
  for(i=0; i<e->nEl; i++) {
    free(e->vet[i].nomeE);
  }
  free(e->vet);
  free(e);
  return 0;
}
