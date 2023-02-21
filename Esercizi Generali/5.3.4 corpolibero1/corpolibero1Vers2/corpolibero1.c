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
  int cnt[CAT];
  float val;
  int diff;
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
  }
  return wrapper;
}

void stampaSol(elementi *e, soluzione *s, char *frase) {
  int i, s_i;
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

float esigenze(elementi *el, soluzione *sol) {
  int cat, nCat, uscita=0, composizione=0;

  /* esigenza di composizione: conta le categorie usate; */
  for(cat=nCat=0;cat<CAT;cat++) {
    if (sol->cnt[cat]>0) nCat++;
  }
  if (nCat>=2) composizione = 1;

  /* controlla ultimo */
  cat = el->vet[sol->sol[EX-1]].categoria;
  if (cat>=AA && el->vet[sol->sol[EX-1]].diff>5) {
    uscita = 1;
  }
  if (nCat==2 && sol->cnt[cat]==1) {
    /* solo due categorie:
       l'ultimo esercizio non deve essere l'unico della sua categoria */
    uscita = 0;
  }
  return (composizione + uscita) * ESIGENZA;
}


/* OTTIMO - modello: combinazioni ripetute - l'ordine non conta - l'ordine conta solo per l'ultimo elemento */

void risolviR(elementi *e, int start, int pos, soluzione *curr, soluzione *best, int *usato, int maxCat[CAT], int maxSUM) {
  int i;
  float toAdd;

  if (pos >= EX) {
    float es = esigenze(e,curr);
    curr->val += es;
    if (best->val <= 0 || curr->val > best->val) {
      *best = *curr;
#if DBG
      stampaSol(e,best,"Soluzione migliorante:");
#endif
    }
    curr->val -= es;
    return;
  }

  for(i=((pos<EX-1)?start:0);i<e->nEl;i++)
    if ((e->vet[i].diff <= maxCat[e->vet[i].categoria]) &&
        (e->vet[i].diff <= (maxSUM - curr->diff))) {
      curr->sol[pos] = i;
      usato[i]++;
      /* aggiungi punti solo se e' la prima occorrenza */
      toAdd = (usato[i] == 1) ? e->vet[i].punti : 0.0 ;
      curr->val += toAdd;
      curr->diff += e->vet[i].diff;
      curr->cnt[e->vet[curr->sol[pos]].categoria]++;
      risolviR(e, i, pos+1, curr, best, usato, maxCat, maxSUM);
      curr->val -= toAdd;
      curr->diff -= e->vet[i].diff;
      curr->cnt[e->vet[curr->sol[pos]].categoria]--;
      usato[i]--;
    }
}

void risolvi(elementi *e, int maxCat[CAT], int maxSUM) {
  soluzione bestSol, currSol;
  int *usato = calloc(e->nEl, sizeof(int));

  bestSol.val = currSol.val = 0.0;
  currSol.diff = 0;
  currSol.cnt[NA] = currSol.cnt[AA] = currSol.cnt[AI] = 0;
  risolviR(e, 0, 0, &currSol, &bestSol, usato, maxCat, maxSUM);

  if (bestSol.val > 0) {
    stampaSol(e,&bestSol,"Soluzione migliore:");
  }
  else
    printf("Soluzione non trovata\n");

  free(usato);
}


/* MAIN */

int main(int argc, char **argv) {
  int i, maxCat[CAT], maxSUM;
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

  printf("Algoritmo completo: combinazioni ripetute su %d elementi, disposizioni sull'ultimo\n",EX-1);
  risolvi(e, maxCat, maxSUM);
  for(i=0; i<e->nEl; i++) {
    free(e->vet[i].nomeE);
  }
  free(e->vet);
  free(e);
  return 0;
}
