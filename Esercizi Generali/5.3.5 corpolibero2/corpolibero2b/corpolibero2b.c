#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define DBG 0
#define MAX 256

/* strutture per rappresentare dati del problema in ingresso:
   la struttura dati comprende anche la parte relativa alla soluzione */

/* elemento di una categoria */
typedef struct {
  char *nomeE;
  float diff;
  float punti;
  int inSol;      /* flag/contatore usato per indicare presenza in soluzione corrente */
  int inBestSol;  /* flag/contatore usato per indicare presenza in soluzione migliore */
} elemento;

/* categoria: si include il contatore k degli elementi selezionati per la categoria */

typedef struct {
  char *nomeC;
  elemento *e;
  int nE;
  int min, max;
  int k;
} categoria;

/* wrapper di più alto livello per vettore di categorie: si includono punti e difficolta'
   di soluzione corrente e migliore */
typedef struct {
  categoria *c;
  int nCat;
  float diffTot, diffTotBest;
  float puntiTot, puntiTotBest;
  int maxD;
} categorie;

/* funzione che fa input e creazione della collezione di categorie */
categorie *leggiFile(FILE *in) {
  int i, j;
  char tmp[MAX];
  categorie *catP = calloc(1, sizeof(categorie));

  if (catP == NULL) return NULL;

  fscanf(in, "%d", &catP->nCat);
  catP->c = calloc(catP->nCat, sizeof(categoria));
  if (catP->c == NULL) return NULL;

  for(i=0;i<catP->nCat;i++) {
    fscanf(in, "%s %d %d %d", tmp, &catP->c[i].nE, &catP->c[i].min, &catP->c[i].max);
    catP->c[i].nomeC = strdup(tmp);
    /* vettore dinamico di elementi di una categoria */
    catP->c[i].e = calloc(catP->c[i].nE, sizeof(elemento));
    if (catP->c[i].e == NULL) return NULL;
    for(j=0;j<catP->c[i].nE;j++) {
      fscanf(in, "%s %f %f", tmp, &catP->c[i].e[j].punti, &catP->c[i].e[j].diff);
      catP->c[i].e[j].nomeE = strdup(tmp);
      /* non necessario (grazie a calloc) ma fatto in modo esplicito come inizializzazione */
      catP->c[i].e[j].inSol = catP->c[i].e[j].inBestSol = 0;
    }
  }
  /* inizializza soluzione migliore con punti (e difficoltà) negativi */
  catP->diffTotBest = -1.0;
  catP->puntiTotBest = -1.0;
  /* inizializza soluzione corrente con punti (e difficoltà) 0 */
  catP->diffTot = 0.0;
  catP->puntiTot = 0.0;

  return catP;
}

/* Funzioni di stampa, principalmente per verifica dei contenuti letti e/o generati */
void stampaElementi(categorie *c) {
  int i, j;
  for(i=0;i<c->nCat;i++) {
    printf("%s min = %d max = %d\n", c->c[i].nomeC,c->c[i].min, c->c[i].max);
    for(j=0;j<c->c[i].nE;j++) {
      printf("   %s p = %.2f d = %.2f\n", c->c[i].e[j].nomeE, c->c[i].e[j].punti,c->c[i].e[j].diff);
    }
  }
}

/* gestione nuova soluzione con aggiornamento della migliore */
void nuovaSoluzione(categorie *catTotP) {
  /* il pruning dovrebbe garantire soluzioni compatibili con il vincolo di difficolta'
     massima: si verifica di non aver fatto errori */
  int i,j;
  if (catTotP->puntiTot > catTotP->puntiTotBest) {
    printf("Soluzione migliorata %.2f %.2f\n", catTotP->puntiTot, catTotP->puntiTotBest);
    /* aggiorna soluzione migliore */
    for(i=0;i<catTotP->nCat;i++) {
      for(j=0;j<catTotP->c[i].nE;j++) {
	catTotP->c[i].e[j].inBestSol = 	catTotP->c[i].e[j].inSol;
      }
    }
    catTotP->diffTotBest = catTotP->diffTot;
    catTotP->puntiTotBest = catTotP->puntiTot;
  }
}


/* generazione ricorsiva della soluzione totale mediante powerset adattato con pruning
   su k (min,max) per categoria e difficolta' massima.
   Tutti i dati sono inclusi nella struttura dati (a partire dal wrapper catTotP).
   la scelta di un elemento viene fatto con un doppio indice (di categoria e di elemento)
   ogni chiamata ricorsiva incrementa l'indice di elemento, internamente (alla funzione chiamata)
   si gestisce il cambio di categoria quando viene raggiunto il numero di elementi.
*/
void powersetModificato(categorie *catTotP, int iCat, int iEl) {
  float d, p;
  int avanti;

  /* controlla fine categoria */
  if (iEl>=catTotP->c[iCat].nE) {
    /* pruning: controlla vincolo di k minimo */
    if (catTotP->c[iCat].k<catTotP->c[iCat].min) {
      return;
    }
    /* vai a un'altra categoria */
    iCat++; iEl = 0;
  }

  /* Caso terminale con soluzione: terminate tutte le categorie */
  if (iCat >= catTotP->nCat) {
    /* gestione nuova soluzione */
    nuovaSoluzione(catTotP);
    return;
  }

  /* caso ricorsivo 0: non scegliere l'elemento corrente della categoria corrente */
  powersetModificato(catTotP, iCat, iEl+1);

  /* caso ricorsivo 1: prova l'elemento corrente della categoria corrente */
  d = catTotP->c[iCat].e[iEl].diff;
  p = catTotP->c[iCat].e[iEl].punti;
  /* pruning: controllo superamento vincolo difficolta' e massimo k per categoria */
  if (catTotP->diffTot+d <= catTotP->maxD &&
      catTotP->c[iCat].k < catTotP->c[iCat].max) {
    avanti = 0; /* se resta a 0 ripete l'esercizio */
    if (catTotP->c[iCat].e[iEl].inSol) {
      /* non puo' essere 2. Solo una ripetizione */
      if (catTotP->c[iCat].e[iEl].inSol == 1)
        p /= 2; /* dimezza valore per la seconda occorrenza di un elemento */
      else
        p = 0;
    }
    catTotP->diffTot += d;
    catTotP->puntiTot += p;
    catTotP->c[iCat].k++;
    catTotP->c[iCat].e[iEl].inSol++;

    powersetModificato(catTotP, iCat, iEl+avanti);

    catTotP->diffTot -= d;
    catTotP->puntiTot -= p;
    catTotP->c[iCat].k--;
    catTotP->c[iCat].e[iEl].inSol--;
  }

}

/* Wrapper a funzione di risoluzione, con stampa della soluzione */
void risolvi(categorie *cat) {
  int i, j;
  FILE *out;

  powersetModificato(cat, 0, 0);

  /* Stampa della soluzione finale */

  out = fopen("soluzione.txt", "w");

  if (cat->puntiTotBest < 0.0) {
    fprintf(out, "Nessuna soluzione rispetta i vincoli\n");
  } else {
    for(i=0;i<cat->nCat;i++) {
      fprintf(out, "%s\n", cat->c[i].nomeC);
      for(j=0;j<cat->c[i].nE;j++) {
	if (cat->c[i].e[j].inBestSol) {
 	  fprintf(out, "  %s [%.2f/%.2f]\n",
		  cat->c[i].e[j].nomeE, cat->c[i].e[j].punti, cat->c[i].e[j].diff);
	  if (cat->c[i].e[j].inBestSol==2) {
	    /* stampa ripetizione dell'esercizio */
	    fprintf(out, "  %s [%.2f/%.2f]\n",
		  cat->c[i].e[j].nomeE, cat->c[i].e[j].punti/2, cat->c[i].e[j].diff);
	  }
	}
      }
    }
    fprintf(out, "TOT p = %.2f d = %.2f\n", cat->puntiTotBest, cat->diffTotBest);
  }
  fclose(out);
}

/* programma principale */
int main(int argc, char **argv) {
  int i,j;
  FILE *in;
  categorie *c;

  if (argc != 3) {
    printf("Uso: %s file D", argv[0]);
    return -1;
  }

  in = fopen(argv[1], "r");
  c = leggiFile(in);
  if (c == NULL) return -1;
#if DBG
  stampaElementi(c);
#endif
  fclose(in);

  c->maxD = atoi(argv[2]);

  risolvi(c);
  for(i=0;i<c->nCat;i++) {
    for(j=0;j<c->c[i].nE;j++) {
      free(c->c[i].e[j].nomeE);
    }
    free(c->c[i].e);
    free(c->c[i].nomeC);
  }
  free(c->c);
  free(c);
  return 0;
}
