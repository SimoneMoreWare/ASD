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

float esigenze(elementi *el, soluzione *sol) {
  int i, nCat = 0, cnt[CAT] = {0,0,0}, ultimo[CAT] = {-1,-1,-1}, uscita=0, composizione=0;

  /* esigenza di composizione: conta gli elementi delle singole categorie - se almeno due categorie
     presenti allora composizione = 1 */
  sol->ultimo = 7;
  for(i=0;i<EX;i++) {
    int cat = el->vet[sol->sol[i]].categoria;
    if (cnt[cat]==0) nCat++; /* primo nella sua categoria: conta la categoria */
    cnt[cat]++;
    if (cat>=AA && el->vet[sol->sol[i]].diff>5) {
      ultimo[cat]=i;
      sol->ultimo = i; /* segna come ultimo uno qualsiasi degli esercizi adatti */
    }
  }
  if (nCat>=2) composizione = 1;

  /* ultimo esercizio. Si genera l'insieme in qualunque ordine e si cerca se un esercizio
     puo' ottenere bonus se messo per ultimo */
  if (ultimo[AA]>=0||ultimo[AI]>=0) {
    /* c'e' un esercizio che puo' essere inserito come ultimo per avere il bonus */
    uscita = 1;
    if (nCat==2) {
      /* solo due categorie:
         l'ultimo esercizio non deve essere l'unico della sua categoria */
      if (((ultimo[AA]>=0)&&(cnt[AA]>1)) || ((ultimo[AI]>=0)&&(cnt[AI]>1))) {
        /* aggiorna la scelta dell'ultimo esercizio */
        if ((ultimo[AA]>=0)&&(cnt[AA]>1)) {
          sol->ultimo = ultimo[AA];
        }
        else {
          sol->ultimo = ultimo[AA];
        }
      }
      else
        uscita = 0;
    }
  }
  return (composizione + uscita) * ESIGENZA;
}


/* OTTIMO - modello: combinazioni ripetute - l'ordine non conta - l'ordine conta solo per l'ultimo elemento */

void risolviR(elementi *e, int start, int pos, soluzione *curr, soluzione *best, int *usato, int maxCat[CAT], int maxSUM) {
  int i;
  float es, toAdd;

  if (pos >= EX) {
    es = esigenze(e,curr);
    curr->val += es;
    if (best->val <= 0 || curr->val > best->val) {
      *best = *curr;
#if DBG
      printf("es %.2f\n",es);
      stampaSol(e,best,"Soluzione migliorante es:");
#endif
    }
    curr->val -= es;
    return;
  }

  for(i=start;i<e->nEl;i++)
    if ((e->vet[i].diff <= maxCat[e->vet[i].categoria]) &&
        (e->vet[i].diff <= (maxSUM - curr->diff))) {
      curr->sol[pos] = i;
      usato[i]++;
      /* aggiungi punti solo se e' la prima occorrenza */
      toAdd = (usato[i] == 1) ? e->vet[i].punti : 0.0 ;
      curr->val += toAdd;
      curr->diff += e->vet[i].diff;
      risolviR(e, i, pos+1, curr, best, usato, maxCat, maxSUM);
      curr->val -= toAdd;
      curr->diff -= e->vet[i].diff;
      usato[i]--;
    }
}

void risolvi(elementi *e, int maxCat[CAT], int maxSUM) {
  soluzione bestSol, currSol;
  int *usato = calloc(e->nEl, sizeof(int));
  if (usato == NULL)
    exit(-1);

  bestSol.val = currSol.val = 0.0;
  currSol.diff = 0;
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

  printf("Algoritmo completo: combinazioni ripetute su %d elementi\n",EX);
  risolvi(e, maxCat, maxSUM);

  for(i=0; i<e->nEl; i++) {
    free(e->vet[i].nomeE);
  }
  free(e->vet);
  free(e);
  return 0;
}
