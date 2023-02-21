#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "voli.h"


voli_t *allocaVoli () {
  voli_t *vp = malloc(sizeof(voli_t));
  vp->head = NULL; 
  vp->tail = NULL;
  return vp;
}

void liberaVoli (voli_t *vp) {
  linkVolo p, q;
  /* libera nodi in lista */
  for (p=vp->head; p!=NULL; p=q) {
    q = p->next;
    free(p);
  }
  free (vp);
}

orario_t leggiOra (FILE *fp) {
  orario_t ora;
  fscanf(fp,"%d:%d", &ora.h, &ora.m);
  return ora;
}


voli_t *leggiVoli (char *nomeFile, aeroporti_t *tabA) {
  voli_t *tabV;
  volo_t *pv;
  int i, nv;
  char codice1[M2], codice2[M2];
  FILE *f = fopen(nomeFile,"r");
  if (f==NULL) return NULL;
  fscanf(f, "%d",&nv);
  tabV = allocaVoli();
  for (i=0; i<nv; i++) {
    pv = malloc(sizeof *pv);
    fscanf(f, "%s%s%s", codice1, codice2, pv->codiceVolo);
    pv->partenza.citta  = cercaAeroportoC(tabA,codice1);
    pv->arrivo.citta  = cercaAeroportoC(tabA,codice2);
    pv->partenza.ora = leggiOra(f);
    pv->arrivo.ora = leggiOra(f);
    if (tabV->head==NULL) {
      tabV->head = tabV->tail = pv;
    }
    else {
      tabV->tail->next = pv;
      tabV->tail = pv;
    }
  }
  fclose(f);
  return tabV;
}

void scriviVolo (FILE *f, volo_t *vp) {
  fprintf(f, "%s %s %-6s %02d:%02d %02d:%02d\n", 
	  vp->partenza.citta->codice,
	  vp->arrivo.citta->codice,
	  vp->codiceVolo,
	  vp->partenza.ora.h,
	  vp->partenza.ora.m,
	  vp->arrivo.ora.h,
	  vp->arrivo.ora.m
	  );
}

void scriviVoli (char *nomeFile, voli_t *voli) {
  int nv;
  volo_t *p;
  FILE *f;
  if (strcmp(nomeFile,"stdout")==0) {
    f = stdout;
  }
  else {
    f = fopen(nomeFile,"w");
  }
  if (f==NULL) return;
  /* conta voli */
  for (nv=0,p=voli->head; p!=NULL; p = p->next) nv++;
  fprintf(f, "%d\n",nv);
  for (p=voli->head; p!=NULL; p = p->next) {
    scriviVolo(f,p);
  }
  if (strcmp(nomeFile,"stdout")!=0) {
    fclose(f);
  }
}

