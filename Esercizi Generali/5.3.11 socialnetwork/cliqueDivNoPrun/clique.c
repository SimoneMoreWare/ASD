#include<stdlib.h>
#include<string.h>
#include<stdio.h>

#include "ts.h"
#include "list.h"
#include "grafo.h"

/* wrapper per vettore di liste: l'ADT LISTA fornisce funzioni per lista
   di interi, compresa una funzione O(1) che ritorna il numero di elementi
   in lista */
typedef struct {
  lista_t *clArray;
  int n;
  int maxN;
  int maxCl;
} cliques;

graph leggi_file(FILE *in, TS ts);
int check(graph g, int *sol, int nNodi);
void stampaCliques(cliques *clT, TS ts);
void nuovaClique(graph g, int *sol, int nNodi, cliques *clT);
void generaCliquesR(graph g, int *sol, cliques *clT, int pos, int start);
void nuovaPermSempl(graph g, int n, int *perm, int *bestPerm, int *bestW);
void calcolaPermSemplR(graph g, int n, int *perm, int *val, int *mark, int pos, int *bestPerm, int *bestW);
void calcolaStampaCammini(graph g, cliques *clTot, TS ts);
void risolvi(graph g, TS ts);
void verificaInput(graph g, TS ts, char *filename);

int main(int argc, char **argv) {
  graph g = NULL;
  TS ts = TSinit(1);
  FILE *in;

  if (ts == NULL)
    exit(1);
  if (argc != 2) {
    printf("Uso: %s <file_in>\n", argv[0]);
    return(1);
  }
  in = fopen(argv[1], "r");
  if (in == NULL)
    exit(1);
  g = leggi_file(in, ts);
  if (g == NULL)
    exit(1);

  risolvi(g, ts);

  TSlibera(ts);
  GRAPHfree(g);

  return 0;
}

graph leggi_file(FILE *in, TS ts) {
  int id1, id2, w;
  char c[MAXL], r[MAXL];
  graph g;

  while(fscanf(in, "%s %s %d", c, r, &w) == 3) {
    id1 = TScercaOaggiungi(ts, c);
    id2 = TScercaOaggiungi(ts, r);
    if (id1 < 0 || id2 < 0)
      printf("Errore in lettura\n");
  }

  rewind(in);

  g = GRAPHinit(TSnum(ts));
  if (g == NULL)
    return NULL;

  while(fscanf(in, "%s %s %d", c, r, &w) == 3) {
    id1 = TScerca(ts, c);
    id2 = TScerca(ts, r);
    if (id1 >= 0 && id2 >= 0)
      GRAPHinsertE(g, id1, id2, w);
  }

  fclose(in);
  return g;
}


int check(graph g, int *sol, int nNodi) {
  int i, j, v = GRAPHgetNV(g), c;

  /* Check connettivit� */
  for(i=0; i<nNodi; i++) {
    for(j=i+1; j<nNodi; j++) {
      if (!GRAPHadiacenti(g, sol[i], sol[j]))
        return 0; /* Se anche un solo arco (i,j) manca, il grafo non � completo */
    }
  }

  /* Check massimalita' */
  /* cerca un nodo fuori dalla soluzione e connesso a tutti */
  for(i=0; i<v; i++) {
    c = 1;
    for(j=0; j<nNodi; j++) {
      if (sol[j]==i || !GRAPHadiacenti(g, i, sol[j])) {
        c = 0; /* i nella clique o fuori e non connesso a sol[j] */
        break;
      }
    }
    if (c)
      return 0; /* Clique non massimale in quanto puo' essere estesa */
  }

  /* Superato il test di completezza e massimalita' */
  return 1;
}

void risolvi(graph g, TS ts) {
  int i;
  int *sol = calloc(GRAPHgetNV(g), sizeof(int));
  cliques *clTot = calloc(1,sizeof(cliques));

  clTot->maxN = GRAPHgetNV(g);
  clTot->clArray = calloc(clTot->maxN, sizeof(lista_t));
  clTot->n = 0;
  clTot->maxCl = -1;

  generaCliquesR(g, sol, clTot, 0, 0);

  stampaCliques(clTot, ts);

  printf("Indice della clique a cardinalita' massima -> %d [dimensione = %d]\n\n", clTot->maxCl, LISTAnum(clTot->clArray[clTot->maxCl]));

  calcolaStampaCammini(g, clTot, ts);

  for (i=0; i<clTot->n; i++) LISTAfree(clTot->clArray[i]);
  free(clTot->clArray);
  free(clTot);
  free(sol);
}

void generaCliquesR(graph g, int *sol, cliques *clT, int pos, int start) {

  int i, v = GRAPHgetNV(g);
  if (start >= v) {
    nuovaClique(g,sol,pos,clT);
    return;
  }

  /* prova tutti i vertici a partire da start */
  for (i=start; i<v; i++) {
    sol[pos] = i;
    generaCliquesR(g, sol, clT, pos+1, i+1);
  }
  /* non aggiungere nulla. */
  generaCliquesR(g, sol, clT, pos, i);
}


void nuovaClique(graph g, int *sol, int nNodi, cliques *clT) {
  int i;
  if(check(g, sol, nNodi)) { /* test di clique massimale */
    /* Memorizza la nuova clique trovata nella prossima posizione libera */
    lista_t newClique = LISTAinit(); /* Inizializza una lista vuota */
    for(i=0; i<nNodi; i++) {
      LISTAinsert(newClique, sol[i]); /* Inserisci tutti i nodi della clique corrente in lista */
    }
    clT->clArray[clT->n] = newClique;

    if (clT->maxCl<0 || nNodi>LISTAnum(clT->clArray[clT->maxCl]))
      clT->maxCl = clT->n;
    clT->n++;
  }
}

void stampaCliques(cliques *clT, TS ts) {
  int i;
  for(i=0; i<clT->n; i++) {
    printf("Clique #%d:\n", i);
    LISTAshowConNomi(clT->clArray[i], ts);
    printf("\n\n");
  }
}

void calcolaStampaCammini(graph g, cliques *clTot, TS ts) {
  int i, bestW;
  /* Per tutte le clique identificate */
  for(i=0; i<clTot->n; i++) {
    int nN = LISTAnum(clTot->clArray[i]);
    if (nN > 2) { /* Salta coppie di nodi collegate da un arco */
      int *tmpSol = calloc(nN, sizeof(int)); /* Permutazione temporanea in fase di costruzione */
      int *bestSol = calloc(nN, sizeof(int)); /* Permutazione migliore */
      int *mark = calloc(nN, sizeof(int)); /* Mark per escludere quelli gi� presi */
      int *val = calloc(nN, sizeof(int)); /* Accumula i nodi da lista, per comodit� */
      LISTA2vett(clTot->clArray[i], val);
      bestW = 0;
      calcolaPermSemplR(g, nN, tmpSol, val, mark, 0, bestSol, &bestW);
      if (bestW>0) {
        int j;
        printf("Ciclo di valore %d -> per clique %d\n", bestW, i);
        for(j=0; j<nN; j++) printf("%s ", TSleggi(ts, bestSol[j]));
        printf("\n");
      }
      /* Libera tutto prima del prossimo giro */
      free(tmpSol);
      free(bestSol);
      free(mark);
      free(val);
    }
  }
}

void calcolaPermSemplR(graph g, int n, int *perm, int *val, int *mark, int pos, int *bestPerm, int *bestW) {
  int i;
  if (pos >= n) {
    nuovaPermSempl(g, n, perm, bestPerm, bestW);
    return;
  }

  /* Per tutti i nodi... */
  for(i=0; i<n; i++) {
    if (mark[i]==0) {
      perm[pos] = val[i];    /* aggiungilo alla permutazione */
      mark[i] = 1;           /* marca */
      calcolaPermSemplR(g, n, perm, val, mark, pos+1, bestPerm, bestW); /* ricorri */
      mark[i] = 0;           /* backtrack */
    }
  }
}

void nuovaPermSempl(graph g, int n, int *perm, int *bestPerm, int *bestW) {
  int i, w = 0;
  for(i=0; i<n; i++)
    w += GRAPHgetPeso(g, perm[i], perm[(i+1)%n]); /* somma dei pesi, con modulo per gestire l'arco che ritorna all'inizio */

  if (w > *bestW) { /* Se migliora il peso del ciclo di Hamilton per la clique corrente, aggiorna */
    *bestW = w;
    for(i=0; i<n; i++) bestPerm[i] = perm[i];
  }
}


