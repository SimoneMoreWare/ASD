#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "esercizi.h"

void freePiano(linkPiano p) {
  linkPiano iter = p, del = NULL;

  if (p == NULL)
    return;

  while(iter) {
    del = iter;
    iter = iter->next;
    free(del);
  }
}

void stampaEsercizio(esercizio_t e) {
  printf("%s %s %s\n", e.nomeEs, e.catEs, e.tipoEs);
}

void stampaEsercizi(tabEser *esercizi, char* file) {
  int i;
  FILE *fp;

  if(file == NULL)
    fp = stdout;
  else
    fp = fopen(file,"w");

  for(i=0;i<esercizi->nEsercizi;i++)
    stampaEsercizio(esercizi->ve[i]);

  if(file!=NULL)
    fclose(fp);
}

esercizio_t* cercaEsercizio(char *esercizio, tabEser *esercizi) {
  int i;
  for(i=0;i<esercizi->nEsercizi;i++)
    if(!strcmp(esercizio, esercizi->ve[i].nomeEs)) return &esercizi->ve[i];
  return NULL;
}

void caricaEsercizi(tabEser *esercizi){
  FILE *fp;
  char nome[LEN], cat[LEN], tipo[LEN];
  int i = 0;

  fp = fopen("esercizi.txt","r");

  if(fp == NULL) {
    printf("Errore nell'apertura del file\n ");
	exit(-1);
  }

  fscanf(fp, "%d\n", &esercizi->nEsercizi);
  esercizi->ve = calloc(esercizi->nEsercizi, sizeof(tabEser));
  esercizi->dimVett = esercizi->nEsercizi;

  while(fscanf(fp, "%s %s %s\n", nome, cat, tipo) == 3) {
    esercizi->ve[i].nomeEs = strdup(nome);
    esercizi->ve[i].catEs = strdup(cat);
    esercizi->ve[i++].tipoEs = strdup(tipo);
  }
  fclose(fp);
}

void stampaPiano(FILE *fp, linkPiano p) {
  linkPiano iter = NULL;
  for(iter = p; iter != NULL; iter = iter->next)
    fprintf(fp, "%s %d %d\n", iter->p.es->nomeEs, iter->p.set, iter->p.rip);
}

int leggiEsPiano(FILE *fp,  eserPiano_t *p, tabEser *esercizi) {
  char nomeTmp[LEN];
  int set, rip;
  esercizio_t *e;

  if (fscanf(fp, "%s %d %d", nomeTmp, &set, &rip) == 3) {
    p->set = set;
    p->rip = rip;
    e = cercaEsercizio(nomeTmp, esercizi);
    if(e == NULL) {
      free(p);
      return 0;
    }
    p->es = e;
    return 1;
  }
  return 0;
}

linkPiano newNodoPiano(eserPiano_t p, linkPiano next) {
  linkPiano n = calloc(1, sizeof(*n));
  if (n == NULL)
    return NULL;
  n->p = p;
  n->next = next;
  return n;
}

void inserisciInListaPiano(linkPiano *head, linkPiano *tail, eserPiano_t p) {
  linkPiano toAdd = newNodoPiano(p, NULL);
  if (toAdd == NULL)
    return;
  if(*head == NULL) {
    *head = *tail = toAdd;
  } else {
      (*tail)->next = toAdd;
      *tail = toAdd;
  }
}

void caricaPiano(char *codice, linkPiano *head, linkPiano *tail, tabEser *esercizi) {
  eserPiano_t e;
  FILE *in = NULL;
  char filename[50];
  strcpy(filename, codice);
  strcat(filename, ".txt");

  if ((in = fopen(filename, "r")) == NULL) {
    printf("Piano di allenamento non disponibile\n");
    return;
  }

  while(leggiEsPiano(in, &e, esercizi) != 0)
    inserisciInListaPiano(head, tail, e);

#if DBG
  printf("Piano per %s\n", codice);
  stampaPiano(stdout, *head);
#endif /* DBG */
  fclose(in);
}

void aggiornaEsercizioInPiano(linkPiano *head, linkPiano *tail, tabEser *esercizi) {
  linkPiano iter = NULL, prev = NULL;
  eserPiano_t e;
  int deletion = 0;

  printf("Inserire nome set rip (impostare valori a zero per cancellare): ");
  if (leggiEsPiano(stdin, &e, esercizi) == 0)
    return;
  for(iter = *head, prev = NULL; iter != NULL; prev = iter, iter = iter->next) {
    if (strcmp(e.es->nomeEs, iter->p.es->nomeEs) == 0) {
      iter->p.set = e.set;
      iter->p.rip = e.rip;

      if (iter->p.set <= 0 || iter->p.rip <= 0) {
        deletion = 1;
        /* Eliminazione dell'esercizio */
        if (iter == *head && iter == *tail) {
            *head = *tail = NULL;
        } else if (iter == *head) {
          *head = iter->next;
        } else if (iter == *tail) {
          *tail = prev;
          prev->next = NULL;
        } else {
           prev->next = iter->next;
        }
        free(iter);
      }

      break;
    }
  }
  if (!deletion && iter == NULL)
    /* Aggiunge nuovo esercizio */
    inserisciInListaPiano(head, tail, e);
  stampaPiano(stdout, *head);
}

void liberaEsercizi(tabEser *esercizi) {
  int i;
  for(i = 0; i < esercizi->nEsercizi; i++) {
    free(esercizi->ve[i].nomeEs);
    free(esercizi->ve[i].catEs);
    free(esercizi->ve[i].tipoEs);
  }
  free(esercizi->ve);
}

