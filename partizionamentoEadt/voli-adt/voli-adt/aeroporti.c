#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aeroporti.h"
#include "voli.h"

typedef struct {
  int *voli; /* vettore di indici */
  int nv;
  int max;
} arrayVoli_t;

typedef struct {
  char *nomeAeroporto;
  char *nomeCitta;
  char codice[M2];
  arrayVoli_t partenze, arrivi;
} aeroporto_t;

struct aeroporti_s {
  aeroporto_t *elenco;
  int na, nmax;
};

static void leggiStringhe(FILE *fp, char *s1, char *s2, char *s3, char sep1, char sep2);

aeroporti_t *allocaAeroporti (int max) {
  aeroporti_t *ap = malloc(sizeof(aeroporti_t));
  ap->nmax = max;
  ap->na = 0;
  ap->elenco = malloc(max*sizeof(aeroporto_t));
  return ap;
}

void liberaAeroporti (aeroporti_t *ap) {
  int i;
  for (i=0; i<ap->na; i++) {
    free (ap->elenco[i].nomeCitta);
    free (ap->elenco[i].nomeAeroporto);
    if (ap->elenco[i].partenze.max>0) 
      free(ap->elenco[i].partenze.voli);
    if (ap->elenco[i].arrivi.max>0)
      free(ap->elenco[i].arrivi.voli);
  }
  free (ap->elenco);
  free (ap);
}

aeroporti_t *leggiAeroporti (char *nomeFile) {
  aeroporti_t *tutti;
  int i, na;
  char citta[M1], aerop[M1];
  FILE *f = fopen(nomeFile,"r");
  if (f==NULL) return NULL;
  fscanf(f,"%d",&na);
  tutti = allocaAeroporti(na);
  for (i=0; i<na; i++) {
    leggiStringhe(f,tutti->elenco[i].codice,citta,aerop,' ',',');
    tutti->elenco[i].nomeCitta  = strdup(citta);
    tutti->elenco[i].nomeAeroporto  = strdup(aerop);
    tutti->elenco[i].partenze.max = tutti->elenco[i].partenze.nv = 0;
    tutti->elenco[i].partenze.voli = NULL;
    tutti->elenco[i].arrivi.max = tutti->elenco[i].arrivi.nv = 0;
    tutti->elenco[i].arrivi.voli = NULL;
  }
  tutti->na = na;
  fclose(f);
  return tutti;
}

int cercaAeroportoC(aeroporti_t *aeroporti, char *codice) {
  int i;
  for (i=0; i<aeroporti->na; i++) {
    if (strcmp(aeroporti->elenco[i].codice,codice)==0) {
      return i;
    }
  }
  return -1;
}

char *codiceAeroporto(aeroporti_t *aeroporti, int id) {
  if (id<0) return NULL;
  return (aeroporti->elenco[id].codice);
}

void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti) {
  int i;
  FILE *f;
  if (strcmp(nomeFile,"stdout")==0) {
    f = stdout;
  }
  else {
    f = fopen(nomeFile,"w");
  }
  if (f==NULL) return;
  fprintf(f, "%d\n",aeroporti->na);
  for (i=0; i<aeroporti->na; i++) {
    fprintf(f, "%s %s, %s\n", 
	    aeroporti->elenco[i].codice,
	    aeroporti->elenco[i].nomeCitta,
	    aeroporti->elenco[i].nomeAeroporto
	    );
  }
  if (strcmp(nomeFile,"stdout")!=0) {
    fclose(f);
  }
}

static void scriviArrayVoli (FILE *fp, aeroporti_t *aeroporti, voli_t *voli, arrayVoli_t *avp) {
  int i;
  for (i=0; i<avp->nv; i++) {
    scriviVolo(fp,aeroporti,voli,avp->voli[i]);
  }
}

static void ordinaArrayVoli (voli_t *tabV, arrayVoli_t *avp, int partenza) {
  int i, j, nv = avp->nv;
  int tmp, *va = avp->voli;
  /* insertion sort */
  for (i=0; i<nv; i++) {
    tmp = va[i];
    for (j=i-1; j>=0 && greaterOra(tabV,va[j],tmp,partenza); j--) {
      va[j+1] = va[j];
    }
    va[j+1] = tmp;
  }
}

void generaPartenzeArrivi (aeroporti_t *aeroporti, voli_t *voli) {
  int idA, i, n;
  /* conta voli in partenza/arrivo */
  for (i=0; i<numVoli(voli); i++) {
    idA = voloAeroporto(voli,i,1);
    aeroporti->elenco[idA].partenze.max++;
    idA = voloAeroporto(voli,i,0);
    aeroporti->elenco[idA].arrivi.max++;
  }
  /* alloca vettori */
  for (i=0; i<aeroporti->na; i++) {
    n = aeroporti->elenco[i].partenze.max;
    if (n>0) {
      aeroporti->elenco[i].partenze.voli = malloc(n*sizeof(int));
    }
    n = aeroporti->elenco[i].arrivi.max;
    if (n>0) {
      aeroporti->elenco[i].arrivi.voli = malloc(n*sizeof(int));
    }
  }
  /* copia indici a voli */
  for (i=0; i<numVoli(voli); i++) {
    /* i e' l'indice del volo */
    idA = voloAeroporto(voli,i,1);
    /* idA e' l'indice dell'aeroporto di partenza */
    aeroporti->elenco[idA].partenze.voli[aeroporti->elenco[idA].partenze.nv++] = i; 
    idA = voloAeroporto(voli,i,0);
    /* idA e' l'indice dell'aeroporto di arrivo */
    aeroporti->elenco[idA].arrivi.voli[aeroporti->elenco[idA].arrivi.nv++] = i;
  }
  /* ordina tabelloni */
  for (i=0; i<aeroporti->na; i++) {
    ordinaArrayVoli (voli,&(aeroporti->elenco[i].partenze), 1);
    ordinaArrayVoli (voli,&(aeroporti->elenco[i].arrivi), 0);
  }
}

void scriviPartenzeArrivi (char *nomeFile, aeroporti_t *aeroporti, voli_t *voli) {
  int i;
  FILE *f;
  if (strcmp(nomeFile,"stdout")==0) {
    f = stdout;
  }
  else {
    f = fopen(nomeFile,"w");
  }

  if (f==NULL) return;
  for (i=0; i<aeroporti->na; i++) {
    fprintf(f, "\nAEROPORTO: %s %s, %s\n", 
	    aeroporti->elenco[i].codice,
	    aeroporti->elenco[i].nomeCitta,
	    aeroporti->elenco[i].nomeAeroporto
	    );
    fprintf(f, "PARTENZE\n");
    scriviArrayVoli (f, aeroporti, voli, &(aeroporti->elenco[i].partenze));
    fprintf(f, "ARRIVI\n");
    scriviArrayVoli (f, aeroporti, voli, &(aeroporti->elenco[i].arrivi));
  }
  if (strcmp(nomeFile,"stdout")!=0) {
    fclose(f);
  }
}

static void leggiStringhe(FILE *fp, char *s1, char *s2, char *s3, char sep1, char sep2) {
  int i;
  char c;
  fscanf(fp," ");
  for (i=0; (fscanf(fp,"%c", &c) != EOF) && c!=sep1; i++) {
    s1[i] = c;
  }
  s1[i] = '\0';
  fscanf(fp," ");
  for (i=0; (fscanf(fp,"%c", &c) != EOF) && c!=sep2; i++) {
    s2[i] = c;
  }
  s2[i] = '\0';
  fscanf(fp," ");
  for (i=0; (fscanf(fp,"%c", &c) != EOF) && c!='\n'; i++) {
    s3[i] = c;
  }
  s3[i] = '\0';
}
