#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "voli.h"

voli_t *allocaVoli (int max) {
  voli_t *vp = malloc(sizeof(voli_t));
  vp->nmax = max;
  vp->nv = 0;
  vp->elenco = malloc(max*sizeof(volo_t));
  return vp;
}

void liberaVoli (voli_t *vp) {
  free (vp->elenco);
  free (vp);
}

orario_t leggiOra (FILE *fp) {
  orario_t ora;
  fscanf(fp,"%d:%d", &ora.h, &ora.m);
  return ora;
}

voli_t *leggiVoli (char *nomeFile, aeroporti_t *aeroporti) {
  voli_t *voli;
  int i, nv;
  char codice1[M2], codice2[M2];
  FILE *f = fopen(nomeFile,"r");
  if (f==NULL) return NULL;
  fscanf(f, "%d",&nv);
  voli = allocaVoli(nv);
  for (i=0; i<nv; i++) {
    fscanf(f, "%s%s%s", codice1, codice2, voli->elenco[i].codiceVolo);
    voli->elenco[i].partenza.idCitta = cercaAeroportoC(aeroporti,codice1);
    voli->elenco[i].arrivo.idCitta = cercaAeroportoC(aeroporti,codice2);
    voli->elenco[i].partenza.ora = leggiOra(f);
    voli->elenco[i].arrivo.ora = leggiOra(f);
  }
  voli->nv = nv;
  voli->aeroporti = aeroporti;
  fclose(f);
  return voli;
}

void scriviVolo (FILE *f, voli_t *voli, int id) {
  volo_t *vp = &(voli->elenco[id]);
  fprintf(f, "%s %s %-6s %02d:%02d %02d:%02d\n", 
	  voli->aeroporti->elenco[vp->partenza.idCitta].codice,
	  voli->aeroporti->elenco[vp->arrivo.idCitta].codice,
	  vp->codiceVolo,
	  vp->partenza.ora.h,
	  vp->partenza.ora.m,
	  vp->arrivo.ora.h,
	  vp->arrivo.ora.m
	  );
}

void scriviVoli (char *nomeFile, voli_t *voli) {
  int i;
  FILE *f;
  if (strcmp(nomeFile,"stdout")==0) {
    f = stdout;
  }
  else {
    f = fopen(nomeFile,"w");
  }
  if (f==NULL) return;
  fprintf(f, "%d\n",voli->nv);
  for (i=0; i<voli->nv; i++) {
    scriviVolo(f,voli,i);
  }
  if (strcmp(nomeFile,"stdout")!=0) {
    fclose(f);
  }
}
