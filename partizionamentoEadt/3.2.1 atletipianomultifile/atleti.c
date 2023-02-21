#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "atleti.h"

int leggiAtleta(FILE *fp, atleta_t *a, categorie_t *categorie) {
  char codiceTmp[LEN], nomeTmp[LEN], cognomeTmp[LEN], categoriaTmp[LEN], dataTmp[LEN];
  int k, ore;
  if (fscanf(fp, "%s %s %s %s %s %d", codiceTmp, cognomeTmp, nomeTmp, categoriaTmp, dataTmp, &ore) == 6) {
    a->codice = strdup(codiceTmp);
    a->cognome = strdup(cognomeTmp);
    a->nome = strdup(nomeTmp);
    /* Gestione categoria */
    {
      k=0;
      while (k < categorie->nCategorie && strcmp(categorie->vc[k].nome, categoriaTmp) != 0)
        k++;
      if ( k == categorie->nCategorie) { /*categoria non trovata (primo elemento per tale categoria */
        if (categorie->nCategorie == categorie->dimVett) {
          categorie->dimVett *= 2;
          categorie->vc = realloc (categorie->vc, categorie->dimVett*sizeof(categoria_t));
        }
        categorie->vc[k].nome = strdup(categoriaTmp);
        categorie->nCategorie++;
      }
      a->categoria = k;
    }

    parsificaData(dataTmp, &(a->data));
    a->ore = ore;
    a->head = a->tail = NULL;
    return 1;
  }
  return 0;
}

linkAtleta newNodoAtleta(atleta_t a, linkAtleta next) {
  linkAtleta n = calloc(1, sizeof(*n));
  if (n == NULL)
    return NULL;
  n->a = a;
  n->next = next;
  return n;
}

void inserisciInListaAtleti(tabAtleti *atleti, atleta_t a) {
  linkAtleta toAdd = newNodoAtleta(a, NULL);
  if (toAdd == NULL)
    return;
  if(atleti->head == NULL)
    atleti->head = atleti->tail = toAdd;
  else {
    atleti->tail->next = toAdd;
    atleti->tail = toAdd;
  }
}

void caricaAnagrafica(tabAtleti *atleti, categorie_t *categorie){
  atleta_t a;
  FILE *fp;
  fp = fopen("atleti.txt","r");

  if(fp == NULL) {
    printf("Errore nell'apertura del file\n ");
	exit(-1);
  }

  categorie->vc = calloc(1, sizeof(categoria_t));
  categorie->nCategorie = 0;
  categorie->dimVett = 1;

   while(leggiAtleta(fp, &a, categorie) != 0)
    inserisciInListaAtleti(atleti, a);
  fclose(fp);
}

void aggiungi(tabAtleti *atleti, categorie_t *categorie){

  atleta_t a;
  printf("Cod Cogn Nome Cat Data Ore: ");
  if (leggiAtleta(stdin, &a, categorie))
    inserisciInListaAtleti(atleti, a);
}

void parsificaData(char strData[], data_t *data) {
  sscanf(strData, "%d/%d/%d", &data->giorno, &data->mese, &data->anno);
}

void stampaAtleta(atleta_t *a, categorie_t *categorie, FILE *fp) {
  fprintf(fp, "%s, %s %s, %s, %d/%d/%d, %d\n", a->codice, a->cognome, a->nome, categorie->vc[a->categoria].nome, a->data.giorno, a->data.mese, a->data.anno, a->ore);
  if (a->head != NULL)
    stampaPiano(stdout, a->head);
}

void stampaAnagrafica(tabAtleti *atleti, categorie_t *categorie, char* file) {
  linkAtleta iter = NULL;
  FILE *fp;
  if(file == NULL)
    fp = stdout;
  else
    fp = fopen(file,"w");

  for(iter = atleti->head;iter != NULL; iter=iter->next)
    stampaAtleta(&(iter->a), categorie, fp);

  if(file!=NULL)
    fclose(fp);
}

void stampaPerCategoria(tabAtleti *atleti, categorie_t *categorie){
  int i;
  linkAtleta iter;

  for(i=0;i<categorie->nCategorie;i++){
	printf("\nNome Categoria: %s\n",categorie->vc[i].nome);
	for(iter = atleti->head; iter != NULL; iter=iter->next) {
      if (iter->a.categoria == i)
		stampaAtleta(&(iter->a), categorie, stdout);
    }
  }
}

int ricercaCodice(tabAtleti *atleti, char* codice, atleta_t *a){
  linkAtleta iter = NULL;

  for(iter = atleti->head; iter != NULL; iter=iter->next) {
    if (strcmp(iter->a.codice, codice) == 0) {
      *a = iter->a;
      return 1;
    }
  }
  return 0;
}

int ricercaCodiceModifica(tabAtleti *atleti, char* codice, int nuoveOre){
  linkAtleta iter = NULL;

  for(iter = atleti->head; iter != NULL; iter=iter->next) {
    if (strcmp(iter->a.codice, codice) == 0) {
	  iter->a.ore = nuoveOre;
      return 1;
	}
  }
  return 0;
}

int ricercaCodiceCaricaPiano(tabAtleti *atleti, tabEser *esercizi, char* codice){
  linkAtleta iter = NULL;
  char filename[50];
  FILE *out;

  for(iter = atleti->head; iter != NULL; iter=iter->next) {
    if (strcmp(iter->a.codice, codice) == 0) {
      if (iter->a.head == NULL) caricaPiano(codice, &iter->a.head, &iter->a.tail, esercizi);
      else {
        strcpy(filename, codice);
        strcat(filename, ".txt");
        out = fopen(filename, "w");
        stampaPiano(out, iter->a.head);
        fclose(out);
      }
      return 1;
    }
  }
  return 0;
}

int ricercaCodiceModificaPiano(tabAtleti *atleti, tabEser *esercizi, char* codice){
  linkAtleta iter = NULL;

  for(iter = atleti->head; iter != NULL; iter=iter->next) {
    if (strcmp(iter->a.codice, codice) == 0) {
      aggiornaEsercizioInPiano(&iter->a.head, &iter->a.tail, esercizi);
      return 1;
    }
  }
  return 0;
}

void freeAtleta(atleta_t a) {
  free(a.codice);
  free(a.nome);
  free(a.cognome);
  if (a.head != NULL) freePiano(a.head);
}

void elimina(tabAtleti *atleti, char* codice){
  linkAtleta iter, prev;

  for(iter = atleti->head, prev = NULL; iter != NULL; prev = iter, iter=iter->next) {
    if (strcmp(iter->a.codice, codice) == 0) {
	  if (iter == atleti->head && iter == atleti->tail) {
  	    atleti->head = atleti->tail = NULL;
	  } else if (iter == atleti->head) {
          atleti->head = iter->next;
	  } else if (iter == atleti->tail) {
		  atleti->tail = prev;
		  prev->next = NULL;
	  } else {
		  prev->next = iter->next;
	  }
	  freeAtleta(iter->a);
	  free(iter);
      break;
    }
  }
}

void ricercaCognome(tabAtleti *atleti, categorie_t *categorie, char* cognome, int nCharConfronto){
  linkAtleta iter;
  int len = strlen(cognome);
  for(iter = atleti->head; iter != NULL; iter=iter->next)
    if (strncmp(iter->a.cognome, cognome, len) == 0) stampaAtleta(&(iter->a), categorie, stdout);
}

void liberaAtleti(tabAtleti *atleti) {
  linkAtleta iter, prev, app;
  for(iter = atleti->head, prev = NULL; iter != NULL; ) {
    app = iter;
    prev = iter;
    iter=iter->next;
    freePiano(app->a.head);
    freeAtleta(app->a);
    free(app);
  }
}

void liberaCategorie(categorie_t *categorie) {
  int i;
  for(i=0;i<categorie->nCategorie;i++) {
    free(categorie->vc[i].nome);
  }
  free(categorie->vc);
}
