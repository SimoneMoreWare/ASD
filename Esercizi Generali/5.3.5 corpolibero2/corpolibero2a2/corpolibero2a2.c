#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define DBG 0
#define MAX 256

#include "sol.h"
#include "arraySol.h"

/* strutture per rappresentare dati del problema in ingresso */

/* elemento di una categoria */
typedef struct {
  char *nomeE;
  float diff;
  float punti;
} elemento;

/* categoria: si include un puntatore (combinazioni) a collezione di combinazioni
   di elementi della categoria
 */
typedef struct {
  char *nomeC;
  elemento *e;
  int nE;
  int min, max;
  ARRAY combinazioni;
} categoria;

/* wrapper di più alto livello per vettore di categorie */
typedef struct {
  categoria *c;
  int nCat;
} categorie;

/* strutture dati per rappresentare le soluzioni del problema */

/* per ogni categoria, gli insiemi di soluzioni sono generati come
   combinazioni di cardinalità in un dati intervallo.
   Ogni soluzione viene tappresentata mediante l'ADT SOL,
   in pratica un "item" realizzato come vettore di interi.
   Per ogni soluzione si rappresentano, oltre alla collezione degli
   elementi, la difficolta' e i punti.
   La collezione di soluzioni viene rappresentata mediante l'ADT
   arraySol, vettore dinamico di combinazioni.
*/

/* La soluzione globale viene calcolata applicando il principio di moltiplicazione
   per selezionare, per ogni categoria, una delle combinazioni precedentemente
   generate. Anche in questo caso si usa una rappresentazione mediante vettore di
   indici (a combinazioni di categorie), difficolta' e punti, sfruttando il tipo
   (ADT) SOL.
 */

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
    }
    /* collezione per soluzione parziale (collezione di elementi): dimensione iniziale
       pari al numero di elementi (ri-allocabile) */
    catP->c[i].combinazioni = ARRAYinit(catP->c[i].nE);
  }

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

void stampaCombinazioni(categorie *c) {
  int i, j, n, cont;
  for(i=0;i<c->nCat;i++) {
    cont = 0;
    n = ARRAYsize(c->c[i].combinazioni);
    for(j=0;j<n;j++) {
      cont++;
    }
  }
}

/* gestione soluzioni/combinazioni di una data categoria */

/* aggiunge una soluzione (duplicata) a una categoria */
void nuovaCombCategoria(categoria *catP, SOL solP) {
  ARRAYpushWithDup(catP->combinazioni, solP);
}

/* generazione ricorsiva delle soluzioni/combinazioni con ripetizione
   di una data categoria:
   - pos e' il numero di elementi gia' inseriti
   - start e' l'indice del primo elemento da considerare, viene gestito
     in modo da evitare piu' di una ripetizione (la seconda volta vale
     la meta', la terza si evita in quanto avrebbe valore 0)
   - D e' il vincolo totale massimo sulla difficolta': viene qui utilizzato
     per un pruning interno alla categoria.
*/
void combRipetizione(categoria *catP, SOL solP, int pos, int start, int D) {
  int i, k=SOLreadN(solP);

  /* Caso terminale:
     completata la combinazione in quanto pos raggiunge la dimensione prevista */
  if (pos >= k) {
    /* aggiungi soluzione a collezione di questa categoria */
    nuovaCombCategoria(catP,solP);
    return;
  }

  /* caso ricorsivo:
     per tutti gli elementi a partire da start */
  for(i=start;i<catP->nE;i++) {
    /* difficolta' e prezzo dell'elemento */
    float d0, p0;
    float d = catP->e[i].diff;
    float p = catP->e[i].punti;
    int i1 = i;
    if (pos>0 && SOLreadI(solP,pos-1)==start) {
      int flagRepeated = 0,k;
      for(k = pos -1; k >= 0; k--) {
        if(SOLreadI(solP,k)==i1) {
          flagRepeated++;
        }
      }
      if(flagRepeated == 1)
        p /= 2;
      else if (flagRepeated >= 2)
             p = 0;
    }
    d0 = SOLreadD(solP);
    p0 = SOLreadP(solP);
    if (d0+d <= D) {
      /* pruning: si ricorre solo se la difficolta' di categoria è compatibile
         con la difficolta' (complessiva) massima */
      SOLwriteI(solP,pos,i);
      SOLwriteD(solP,d0+d);
      SOLwriteP(solP,p0+p);
      combRipetizione(catP, solP, pos+1, i1, D);
      /* backtrack: ripristina valori precedenti */
      SOLwriteD(solP,d0);
      SOLwriteP(solP,p0);
    }
  }
}

/* gestione soluzione complessiva come insieme di soluzioni/combinazioni su singole categorie */


/* Funzioni (ausiliarie) per il principio di moltiplicazione */
void nuovaSoluzione(categorie *catTotP, SOL solTotP, SOL bestP, int D) {
  /* il pruning dovrebbe garantire soluzioni compatibili con il vincolo di difficolta'
     massima: si verifica di non aver fatto errori */
  assert (SOLreadD(solTotP) <= D);
  if (SOLreadP(solTotP) > SOLreadP(bestP)) {
    printf("Soluzione migliorata %.2f %.2f\n", SOLreadP(solTotP), SOLreadP(bestP));
    SOLcopy(bestP,solTotP);
  }
}

/* generazione ricorsiva della soluzione totale mediante principio di moltiplicazione
   sulle categorie (per le quali sono gia' disponibili le collezioni di soluzioni/combinazioni,
   ognuna caratterizzata da punteggio e difficolta'.
*/
void princMolt(categorie *catTotP, SOL solTotP, SOL bestP, int pos, int D) {
  int i, nComb;

  /* caso terminale: terminate le categorie */
  if (pos >= catTotP->nCat) {
    nuovaSoluzione(catTotP, solTotP, bestP, D);
    return;
  }

  nComb = ARRAYsize(catTotP->c[pos].combinazioni);

  for(i=0;i<nComb;i++) {
    SOL solCatP = ARRAYread(catTotP->c[pos].combinazioni,i);
    float d0, p0;
    float d = SOLreadD(solCatP);
    float p = SOLreadP(solCatP);
    d0 = SOLreadD(solTotP);
    p0 = SOLreadP(solTotP);
    if (d0+d <= D) {
      SOLwriteD(solTotP,d0+d);
      SOLwriteP(solTotP,p0+p);
      SOLwriteI(solTotP,pos,i);
      princMolt(catTotP, solTotP, bestP, pos+1, D);
      SOLwriteD(solTotP,d0);
      SOLwriteP(solTotP,p0);
    }
  }
}


/* Intero blocco risolutivo */

void risolvi(categorie *cat, int D) {
  int i, k, j, iComb, el;
  SOL solTot, bestTot, solCatP;
  FILE *out;
  /* STEP 1 - Genera tutti i possibili sottoinsiemi per ogni categoria
     usando parzialmente i vincoli: i sottoinsiemi tengono conto della
     difficolta' massima (applicata all'interno di una sola categoria)
  */

  for(i=0;i<cat->nCat;i++) {
    /* Per comodità salva i singoli campi in variabili temporanee */
    int min = cat->c[i].min;
    int max = cat->c[i].max;
    SOL solP;

    /* si alloca una soluzione compatibile con dimensione massima */
    solP = SOLnew(max);
    /* combinazioni di dimensione crescente tra min e max */
    for(k=min;k<=max;k++) {
      SOLwrite(solP, 0.0, 0.0);
      SOLwriteN(solP, k);
      combRipetizione(&(cat->c[i]), solP, 0, 0, D);
    }
    SOLfree(solP);
  }
#if DBG
  stampaCombinazioni(cat);
#endif

  solTot = SOLnew(cat->nCat);
  SOLwriteN(solTot,cat->nCat);
  bestTot = SOLnew(cat->nCat);
  SOLwriteN(bestTot,cat->nCat);

  /* inizializza soluzione migliore con punti (e difficoltà) negativi */
  SOLwriteD(bestTot,-1.0);
  SOLwriteP(bestTot,-1.0);

  princMolt(cat, solTot, bestTot, 0, D);

  /* STEP 3 - Stampa della soluzione finale */

  out = fopen("soluzione.txt", "w");

  if (SOLreadP(bestTot) < 0.0) {
    fprintf(out, "Nessuna soluzione rispetta i vincoli\n");
  } else {
    for(i=0;i<cat->nCat;i++) {
      fprintf(out, "%s\n", cat->c[i].nomeC);
      iComb = SOLreadI(bestTot,i);
      solCatP = ARRAYread(cat->c[i].combinazioni,iComb);
      for(j=0;j<SOLreadN(solCatP);j++) {
        el = SOLreadI(solCatP,j);
        fprintf(out, "  %s [%.2f/%.2f]\n", cat->c[i].e[el].nomeE, cat->c[i].e[el].punti, cat->c[i].e[el].diff);
      }
    }
    fprintf(out, "TOT p = %.2f d = %.2f\n", SOLreadP(bestTot), SOLreadD(bestTot));
  }

  SOLfree(solTot);
  SOLfree(bestTot);
  fclose(out);
}

int main(int argc, char **argv) {
  int i,j, D;
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
#endif /* DBG */
  fclose(in);

  D = atoi(argv[2]);

  risolvi(c, D);
  for(i=0;i<c->nCat;i++) {
    for(j=0;j<c->c[i].nE;j++) {
      free(c->c[i].e[j].nomeE);
    }
    free(c->c[i].e);
    free(c->c[i].nomeC);
    ARRAYfree(c->c[i].combinazioni);
  }
  free(c->c);
  free(c);
  return 0;
}
