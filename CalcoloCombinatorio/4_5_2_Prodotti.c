#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXRIGA 100

typedef struct datiProdotto {
  char *nomeProdotto;
  int numeroFornitori;
  int *elencoFornitori;
} datiprod;

void cercaSoluzione (char **fornitori, datiprod *prodotti, 
                     int *acquisti,int nf, int np, int na);
void cercaSoluzioneRicorsiva(char **fornitori, datiprod *prodotti,
                             int *acquisti, int nf, int np, int na, 
                             int *scelta,int *sceltamigliore, 
                             int *pnm, int inizio, int nScelte);

void sortStringhe(char **fornitori, int nf);
int ricercaBinariaStringa(char **fornitori, int nf, char *nomef);
void sortProdotti(datiprod *prodotti, int np);
int ricercaBinariaProdotto(datiprod *prodotti, int np, char *nomep);
char **fornitori;

void main (void) {
  FILE *fp;
  char riga[MAXRIGA], nomep[MAXRIGA], nomef[MAXRIGA];
  int nf, np, nfi, na, i, j;
  char **fornitori;
  datiprod *prodotti;
  int *acquisti;

  fp = fopen("elenco.txt","r");

  /* lettura nf e np - allocazione vettori dinamici per nomi */
  fgets(riga,MAXRIGA-1,fp);
  sscanf(riga, "%d%d", &nf, &np);
  fornitori = malloc(nf * sizeof(char *));
  prodotti = malloc(np * sizeof(datiprod));
  acquisti = malloc(np * sizeof(int));

  /* acquisizione nomi fornitori */
  for (i = 0; i < nf; i++) {
    fgets(riga,MAXRIGA-1,fp);
    sscanf(riga,"%s", nomef);
    fornitori[i] = malloc((strlen(nomef)+1) * sizeof(char));
    strcpy(fornitori[i],nomef);
  }

  /* sorting alfabetico fornitori per consentire ricerca binaria */
  sortStringhe(fornitori,nf);

  /* acquisizione prodotti con liste fornitori*/
  for (i = 0; i < np; i++) {
    fgets(riga,MAXRIGA-1,fp);
    sscanf(riga,"%s%d", nomep, &nfi);
    prodotti[i].nomeProdotto=malloc((strlen(nomep)+1)*sizeof(char));
    strcpy(prodotti[i].nomeProdotto,nomep);
    prodotti[i].numeroFornitori = nfi;
    prodotti[i].elencoFornitori = malloc(nfi * sizeof(int));
    for (j = 0; j < nfi; j++) {
      fgets(riga,MAXRIGA-1,fp);
      sscanf(riga,"%s", nomef);
      prodotti[i].elencoFornitori[j] = 
        ricercaBinariaStringa(fornitori,nf,nomef);
    }
  }

  /* sorting alfabetico prodotti per consentire ricerca binaria */
  sortProdotti(prodotti,np);

  fclose(fp);
  fp = fopen("acquisti.txt","r");

  na = 0;
  while (fscanf(fp,"%s",nomep)!=EOF) {
    i = ricercaBinariaProdotto(prodotti,np,nomep);
    acquisti[na++] = i;    
  }

  fclose(fp);
  cercaSoluzione(fornitori,prodotti,acquisti,nf,np,na);
}

void cercaSoluzione (
  char **fornitori,
  datiprod *prodotti,
  int *acquisti,
  int nf,
  int np,
  int na
) {
  int i, j, k, f, trovato,fmax,numMigliore;
  int *scelta, *sceltaMigliore;

  scelta = malloc(nf * sizeof(int));
  sceltaMigliore = malloc(nf * sizeof(int));

  for (i = 0; i < nf; i++) {
    scelta[i] = 0;
    sceltaMigliore[i] = 1; /* si inizia con tutti i fornitori */
  }
  numMigliore = nf; /* inizialmente tutti i fornitori */

  cercaSoluzioneRicorsiva(fornitori, prodotti, acquisti, nf, np, 
                          na, scelta, sceltaMigliore, 
                          &numMigliore, 0, 0);

  /* stampa elenco dei fornitori */
  printf ("L'insieme di fornitori prescelto ricorsivamente e':\n");
  for (i = 0; i < nf; i++) {
    if (sceltaMigliore[i] == 1) {
      printf("%s\n", fornitori[i]);
    }
  }

  free(scelta);
  free(sceltaMigliore);
}

void cercaSoluzioneRicorsiva(
  char **fornitori,
  datiprod *prodotti,
  int *acquisti,
  int nf,
  int np,
  int na,
  int *scelta,
  int *sceltaMigliore,
  int *pnm,
  int inizio,
  int nScelte
) {
  int f, i, j, p;

  /* caso terminale */

  if (inizio >= na) {
    /* terminati i prodotti: confronta con soluzione migliore */
    if (nScelte < *pnm) {
      *pnm = nScelte;
      for (i = 0; i < nf; i++) {
        sceltaMigliore[i] = scelta[i];
      }
    }
    return;
  }

  /* seleziona il prodotto acquistato */
  p = acquisti[inizio];

  /* prova tutti i fornitori e attiva un sotto-problema ricorsivo */
  for (j = 0; (j < prodotti[p].numeroFornitori); j++) {
    f = prodotti[p].elencoFornitori[j];
    if (scelta[f] == 0) {
      /* f non ancora scelto: aggiungi prima di ricorrere e togli dopo */
      scelta[f] = 1;
      nScelte++;
      cercaSoluzioneRicorsiva(fornitori, prodotti, acquisti, nf, np, 
                              na, scelta, sceltaMigliore, pnm, 
                              inizio+1, nScelte);
      nScelte--;
      scelta[f] = 0;
    }
    else {
      /* f gia' scelto: nulla da aggiungere e togliere */
      cercaSoluzioneRicorsiva(fornitori, prodotti, acquisti, nf, np, 
                              na, scelta, sceltaMigliore, pnm, 
                              inizio+1, nScelte);
    }
  }
}
