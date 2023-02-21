#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ts.h"

#define MAX_STR 31
#define MAX_CAT 10
#define MAX_PROD 50
#define MAX_DITTE 20

typedef struct prodotto {
  int indiceCategoria;
  int indiceNome;
  int indiceDitta;
} Prodotto;

int input(char *nomefile, Prodotto *prodotti, TS tabC, TS tabN, TS tabD);
void forniture(Prodotto *prod, int nProd, TS tabC, TS tabN, TS tabD, int k);
void fornRicorsiva(int *npla, int *conteggi, Prodotto *prodotti, TS tabC,
                   TS tabN, TS tabD, int cat, int nP, int nC, int nD, int k);

int main(int argc, char **argv) {
  int k, nProd;
  TS tabCategorie, tabNomi, tabDitte;
  Prodotto prod[MAX_PROD];

  if (argc < 3) {
    fprintf(stderr, "Uso: %s <file> <k>\n", argv[0]);
    exit(-1);
  }
  k = atoi (argv[2]);

  tabCategorie = TScrea(MAX_CAT);
  tabNomi = TScrea(MAX_PROD);
  tabDitte = TScrea(MAX_DITTE);

  nProd = input(argv[1],prod,tabCategorie,tabNomi,tabDitte);

  forniture(prod,nProd,tabCategorie,tabNomi,tabDitte,k);

  TSlibera(tabCategorie);
  TSlibera(tabNomi);
  TSlibera(tabDitte);

  return 0;
}

/* funzione usata unicamente per preparare i vettore delle soluzioni (npla)
   e dei conteggi (per ditta) e chiamare fornRicorsiva */
void forniture(Prodotto *prod, int nProd, TS tabC, TS tabN, TS tabD, int k) {
  int i, nCat = TSdimensione(tabC), nDitte = TSdimensione(tabD);
  int npla[MAX_CAT]; /* sovradimensionato,
                        potrebbe essere allocato dinamicamente (nCat); */
  int conteggi[MAX_DITTE];
  for (i=0; i<nDitte; i++) conteggi[i] = 0;
  fornRicorsiva(npla,conteggi,prod,tabC,tabN,tabD,0,nProd,nCat,nDitte,k);
}

/* versione con pruning, basato su vettore dei conteggi, aggiornato
   dinamicamente, con backtrack */
void fornRicorsiva(int *npla, int *conteggi, Prodotto *prodotti, TS tabC,
                   TS tabN, TS tabD, int cat, int nP, int nC, int nD, int k) {
  int i, p;

  /* caso terminale. Tutte le categorie già coperte. stampa fornitura */
  if (cat == nC) {
    for(i=0;i<nC;i++) {
      char *nomeProd, *nomeDitta;
      p = npla[i];
      nomeProd = TSleggiIndice(tabN, prodotti[p].indiceNome);
      nomeDitta = TSleggiIndice(tabD, prodotti[p].indiceDitta);
      fprintf(stdout, " %12s (%10s)", nomeProd, nomeDitta);
    }
    fprintf(stdout, "\n");
    return;
  }

  /* caso ricorsivo. Seleziona prodotti della categoria cercata.
     Prova, ricorre e fa backtrack. */
  for (p=0; p<nP; p++) {
    if (prodotti[p].indiceCategoria == cat) {
      /* categoria selezionata. controlla il conteggio della ditta */
      int d = prodotti[p].indiceDitta;
      if (conteggi[d]<k) {
        /* assegna indice del prodotto selezionato, nel vettore npla. */
        npla[cat] = p;
        /* aggiorna conteggio ditta */
        conteggi[d]++;
        /* ricorri su categoria successiva */
        fornRicorsiva(npla,conteggi,prodotti,tabC,tabN,tabD,
                      cat+1,nP,nC,nD,k);
        /* backtrack solo su conteggi perche' npla vera' sovrascritto */
        conteggi[d]--;
      }
    }
  }

}

int input(char *nomefile, Prodotto *prodotti, TS tabC, TS tabN, TS tabD) {
  char cat[MAX_STR], nome[MAX_STR], ditta[MAX_STR];

  FILE *fp = fopen(nomefile, "r");
  int np;

  if (fp==NULL) {
    fprintf(stderr, "Errore aprendo %s\n", nomefile);
    exit(-1);
  }

  /* leggi il file a terne di stringhe */
  for (np=0; !feof(fp)&&fscanf(fp,"%s%s%s", cat, nome, ditta)==3; np++) {
    /* aggiorna tabelle e genera indici.
       Genera nuova riga nel vettore dei prodotti.
       Si suppone che non ci siano errori nel file */
    /* printf("Ho letto: %s %s %s -> ", cat,nome,ditta); */
    prodotti[np].indiceCategoria = TScercaOAggiungi(tabC,cat);
    prodotti[np].indiceNome = TScercaOAggiungi(tabN,nome);
    prodotti[np].indiceDitta = TScercaOAggiungi(tabD,ditta);
    /* printf("indici: %d %d %d\n", prodotti[np].indiceCategoria,
       prodotti[np].indiceNome, prodotti[np].indiceDitta); */
  }

  fclose(fp);

  return np;
}
