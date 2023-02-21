#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DBG 0
#define MAX 256

/*
 * Organizzazione della soluzione
 * - Lettura del file e memorizzazione dei contenuti
 * - Generazione delle combinazioni di elementi per ogni categoria
 *   > Insiemi tutti lunghi quanti sono gli elementi disponibili, per comodità di uso
 *   > Un intero a rappresentare il numero di ripetizione di un elemento
 *   > Combinazioni con ripetizione di n elementi in classe k, con k da min_i a max_i
 * - Generazione di tutti i possibili programmi liberi mediante principio di moltiplicazione
 */

/* Definizione delle strutture dati */

typedef struct elemento_ {
  char *nomeE;
  float diff;
  float punti;
} elemento;

typedef struct categoria_ {
  elemento *e;
  char *nomeC;
  int nElementi;
  int min, max;
} categoria;

typedef struct categorie_ {
  categoria *c;
  int nCat;
} categorie;

typedef struct combinazione_ {
  int *vett;
  float diff;
  float punti;
} combinazione;

typedef struct combinazioniCat_ {
  combinazione *c;
  int nCombinazioniCat;
} combinazioniCat;

typedef struct combinazioni_ {
  combinazioniCat *cCat;
  int nCat;
} combinazioni;

/* Funzioni di input */

categorie *leggiFile(FILE *in) {
  int i, j;
  char tmp[MAX];
  categorie *wrapper = calloc(1, sizeof(categorie));
  if (wrapper == NULL) return NULL;

  fscanf(in, "%d", &wrapper->nCat);
  wrapper->c = calloc(wrapper->nCat, sizeof(categoria));
  if (wrapper->c == NULL) return NULL;

  for(i=0;i<wrapper->nCat;i++) {
    fscanf(in, "%s %d %d %d", tmp, &wrapper->c[i].nElementi, &wrapper->c[i].min, &wrapper->c[i].max);
    wrapper->c[i].nomeC = strdup(tmp);
    if(wrapper->c[i].nomeC == NULL) return NULL;

    wrapper->c[i].e = calloc(wrapper->c[i].nElementi, sizeof(elemento));
    if (wrapper->c[i].e == NULL) return NULL;

    for(j=0;j<wrapper->c[i].nElementi;j++) {
      fscanf(in, "%s %f %f", tmp, &wrapper->c[i].e[j].punti, &wrapper->c[i].e[j].diff);
      wrapper->c[i].e[j].nomeE = strdup(tmp);
      if(wrapper->c[i].e[j].nomeE == NULL) return NULL;
    }
  }

  return wrapper;
}

/* Funzioni di stampa, principalmente per verifica dei contenuti letti e/o generati */

void stampaElementi(categorie *c) {
  int i, j;
  for(i=0;i<c->nCat;i++) {
    printf("%s min = %d max = %d\n", c->c[i].nomeC,c->c[i].min, c->c[i].max);
    for(j=0;j<c->c[i].nElementi;j++) {
      printf("   %s p = %.2f d = %.2f\n", c->c[i].e[j].nomeE, c->c[i].e[j].punti,c->c[i].e[j].diff);
    }
  }
}

void stampaCombinazioni(categorie *c, combinazioni *allComb) {
  int i, j, k;
  for(i=0;i<allComb->nCat;i++) {
    printf("%s\n", c->c[i].nomeC);
    for(j=0;j<allComb->cCat[i].nCombinazioniCat;j++) {
      for(k=0;k<c->c[i].nElementi;k++) {
        printf("%d ", allComb->cCat[i].c[j].vett[k]);
      }
      printf(" p = %.2f d = %.2f\n", allComb->cCat[i].c[j].punti, allComb->cCat[i].c[j].diff);
    }
  }
}

/* Funzioni (ausiliarie) per la generazione delle combinazioni */

 int numCombinazioni(int n, int k) {
  int i;
  double num = 1, den = 1;
  for(i=k;i>0;i--) {
    num *= n;
    den *= k;
    n--;
    k--;
  }
  return num/den;
 }

void combRipetizione(int pos, categoria c, int *sol, int n, int k, int start, int *count, combinazioniCat cCat) {
  int i;
  float rip;
  /* Completata la combinazione */
  if (pos >= k) {
    /* Per ogni possibile elemento */
    for(i=0;i<n;i++) {
        /* Copia il numero di ripetizioni */
        cCat.c[*count].vett[i] = sol[i];
        /* Incrementa il valore della difficoltà della combinazione attuale */
        cCat.c[*count].diff += (sol[i] * c.e[i].diff);
        /* Valuta l'incremento di punteggio, tenendo conto della deduzione per elementi uguali */
        rip = sol[i] > 1 ? 1.5 : (float) sol[i];
        cCat.c[*count].punti += (rip * c.e[i].punti);
    }
    (*count)++;
    return;
  }
  for(i=start;i<n;i++) {
    /* L'elemento 'i' viene eseguito una volta (in più) rispetto alla combinazione attuale */
    sol[i]++;
    combRipetizione(pos+1, c, sol, n, k, i, count, cCat);
    /* Poiché non memorizza la combinazione come insieme ma per ripetizioni, serve fare 'backtrack' sulla struttura dati */
    sol[i]--;
  }
}

/* Funzioni (ausiliarie) per il principio di moltiplicazione */

void princMolt(int pos, float curr_diff, float curr_p, combinazioni *c, int *sol, int *sol_best, float *best, float *diff, int D) {
  int i;
  if (pos >= c->nCat) {
    if ((*best < 0) || (*best) < curr_p) {
#if DBG
      printf("Soluzione migliorata %.2f %.2f\n", curr_diff, curr_p);
#endif
      for(i=0;i<c->nCat;i++) {
        sol_best[i] = sol[i];
      }
      *best = curr_p;
      *diff = curr_diff;
    }
    return;
  }
  for(i=0;i<c->cCat[pos].nCombinazioniCat;i++) {
    if (curr_diff + c->cCat[pos].c[i].diff <= D) {
      sol[pos] = i;
      princMolt(pos+1, curr_diff + c->cCat[pos].c[i].diff, curr_p + c->cCat[pos].c[i].punti, c, sol, sol_best, best, diff, D);
    }
  }
}

/* Intero blocco risolutivo */

void risolvi(categorie *c, int D) {
  int i, j;

  /* STEP 1 - Genera tutti i possibili sottoinsiemi per ogni categoria */
  combinazioni *allComb = calloc(1, sizeof(combinazioni));
  allComb->nCat = c->nCat;
  allComb->cCat = calloc(allComb->nCat, sizeof(combinazioniCat));
  /* Per ogni categoria */
  for(i=0;i<allComb->nCat;i++) {
    /* Per comodità salva i singoli campi in variabili temporanee */
    int min = c->c[i].min;
    int max = c->c[i].max;
    int nEl = c->c[i].nElementi;
    /* Conta quante combinazioni con ripetizione possono essere fatte con n elementi e k variabile tra min e max */
    for(j=min;j<=max;j++) allComb->cCat[i].nCombinazioniCat += numCombinazioni(nEl+j-1, j);
    /* Alloca un oggetto di tipo combinazione per ogni possibile insieme */
    allComb->cCat[i].c = calloc(allComb->cCat[i].nCombinazioniCat, sizeof(combinazione));
    /* Alloca il vettore usato per memorizzare ogni possibile combinazione */
    for(j=0;j<allComb->cCat[i].nCombinazioniCat;j++) allComb->cCat[i].c[j].vett = calloc(nEl, sizeof(int));
    /* Genera effettivamente tutte le combinazioni andando a memorizzarle nei vettori appena allocati */
    int count = 0; /* Usa count per scrivere nel vettore opportuno della struttura dati */
    int *sol = calloc(nEl, sizeof(int));
    for(j=min;j<=max;j++) combRipetizione(0, c->c[i], sol, nEl, j, 0, &count, allComb->cCat[i]);
    free(sol);
  }
#if DBG
  stampaCombinazioni(c, allComb);
#endif

  /* STEP 2 - Genera tutte le possibili soluzioni tramite principio di moltiplicazione sulle combinazioni */
  int *sol = calloc(c->nCat, sizeof(int));
  if (sol == NULL)
    exit(-1);
  int *sol_best = calloc(c->nCat, sizeof(int));
  if (sol_best == NULL)
    exit(-1);
  float best = -1, diff = -1;
  princMolt(0, 0.0, 0.0, allComb, sol, sol_best, &best, &diff, D);

  /* STEP 3 - Stampa della soluzione finale */

  FILE *out = fopen("soluzione.txt", "w");

  if (best < 0) {
    fprintf(out, "Nessuna soluzione rispetta i vincoli\n");
  } else {
    for(i=0;i<c->nCat;i++) {
      fprintf(out, "%s\n", c->c[i].nomeC);
      for(j=0;j<c->c[i].nElementi;j++) {
        fprintf(out, "  %s x%d [%.2f/%.2f]\n", c->c[i].e[j].nomeE, allComb->cCat[i].c[sol_best[i]].vett[j], c->c[i].e[j].punti, c->c[i].e[j].diff);
      }
    }
    fprintf(out, "TOT p = %.2f d = %.2f\n", best, diff);
  }
  for(i=0;i<allComb->nCat;i++) {
    for(j=0;j<allComb->cCat[i].nCombinazioniCat;j++) {
      free(allComb->cCat[i].c[j].vett);
    }
    free(allComb->cCat[i].c);
  }
  free(allComb->cCat);
  free(allComb);
  free(sol);
  free(sol_best);
  fclose(out);
}

int main(int argc, char **argv) {
  int i,j;
  if (argc != 3) {
    printf("Uso: %s file D", argv[0]);
    return -1;
  }

  FILE *in = fopen(argv[1], "r");
  categorie *c = leggiFile(in);
  if (c == NULL) return -1;
#if DBG
  stampaElementi(c);
#endif /* DBG */
  fclose(in);

  int D = atoi(argv[2]);

  risolvi(c, D);

  for(i=0;i<c->nCat;i++) {
    for(j=0;j<c->c[i].nElementi;j++) {
      free(c->c[i].e[j].nomeE);
    }
    free(c->c[i].e);
    free(c->c[i].nomeC);
  }
  free(c->c);
  free(c);
  return 0;
}
