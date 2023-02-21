#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "aeroporti.h"

aeroporti_t *allocaAeroporti () {
  aeroporti_t *ap = malloc(sizeof(aeroporti_t));
  ap->head = NULL;
  ap->tail = NULL;
  return ap;
}

void liberaAeroporti (aeroporti_t *ap) {
  linkAeroporto p, q;
  /* libera nodi in lista */
  for (p=ap->head; p!=NULL; p=q) {
    q = p->next;
    free(p->nomeCitta);
    free(p->nomeAeroporto);
    free(p);
  }
  free (ap);
}

void leggiStringhe(FILE *fp, char *s1, char *s2, char *s3, char sep1, char sep2) {
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

aeroporti_t *leggiAeroporti (char *nomeFile) {
  aeroporti_t *tabA;
  aeroporto_t *pa;
  int i, na;
  char citta[M1], aerop[M1];
  FILE *f = fopen(nomeFile,"r");
  if (f==NULL) return NULL;
  fscanf(f,"%d",&na);
  tabA = allocaAeroporti();
  for (i=0; i<na; i++) {
    pa = malloc(sizeof *pa);
    leggiStringhe(f,pa->codice,citta,aerop,' ',',');
    pa->nomeCitta  = strdup(citta);
    pa->nomeAeroporto  = strdup(aerop);
    if (tabA->head==NULL) {
      tabA->head = tabA->tail = pa;
    }
    else {
      tabA->tail->next = pa;
      tabA->tail = pa;
    }
  }
  fclose(f);
  return tabA;
}

aeroporto_t *cercaAeroportoC(aeroporti_t *aeroporti, char *codice) {
  aeroporto_t *p;
  for (p=aeroporti->head; p!=NULL; p = p->next) {
    if (strcmp(p->codice,codice)==0) {
      return p;
    }
  }
  return NULL;
}


void scriviAeroporti (char *nomeFile, aeroporti_t *aeroporti) {
  int na;
  aeroporto_t *p;
  FILE *f;
  if (strcmp(nomeFile,"stdout")==0) {
    f = stdout;
  }
  else {
    f = fopen(nomeFile,"w");
  }
  if (f==NULL) return;
  /* conta aeroporti */
  for (na=0,p=aeroporti->head; p!=NULL; p = p->next) na++;
  fprintf(f, "%d\n",na);
  for (p=aeroporti->head; p!=NULL; p = p->next) {
    fprintf(f, "%s %s, %s\n",p->codice,p->nomeCitta,p->nomeAeroporto);
  }
  if (strcmp(nomeFile,"stdout")!=0) {
    fclose(f);
  }
}

