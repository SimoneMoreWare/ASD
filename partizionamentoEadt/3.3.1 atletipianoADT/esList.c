#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "esList.h"

typedef struct eserPiano_s {
  int set, rip;
  int es;
} eserPiano_t;

typedef struct nodoPiano_s *linkPiano;
typedef struct nodoPiano_s {
  eserPiano_t *p;
  linkPiano next;
} nodoPiano_t;

struct piano_s {
  linkPiano head, tail;
};

linkPiano newNodoPiano(eserPiano_t *p, linkPiano next) {
	linkPiano n = calloc(1, sizeof(*n));
	if (n == NULL) return NULL;
	n->p = p;
	n->next = next;
	return n;
}

void inserisciInListaPiano(esList_t p, eserPiano_t *ep) {
  if (p == NULL) return;
	linkPiano toBeAdded = newNodoPiano(ep, NULL);
	if (toBeAdded == NULL) return;
    if(p->head == NULL) {
      p->head = p->tail = toBeAdded;
    } else {
      p->tail->next = toBeAdded;
      p->tail = toBeAdded;
    }

}

void stampaPiano(FILE *fp, esArray_t esercizi, esList_t p) {
  linkPiano iter = NULL;
  for(iter = p->head; iter != NULL; iter = iter->next) {
    stampaEsercizioVett(esercizi, iter->p->es);
    fprintf(fp, "%d %d\n", iter->p->set, iter->p->rip);
  }
}

eserPiano_t *leggiEsPiano(FILE *fp, esArray_t esercizi) {
  char nomeTmp[LEN];
  int set, rip;
  if (fscanf(fp, "%s %d %d", nomeTmp, &set, &rip) == 3) {
    eserPiano_t *p = calloc(1, sizeof(eserPiano_t));
    p->set = set;
    p->rip = rip;
    p->es = cercaEsercizio(nomeTmp, esercizi);
    if(p->es == -1) {
        free(p);
        return NULL;
    }
    return p;
  }
  return NULL;
}

esList_t esListCaricaPiano(FILE *fp, esArray_t esercizi) {
  esList_t p = calloc(1, sizeof(*p));
  if (p == NULL) return p;
  eserPiano_t *ep;
  while((ep = leggiEsPiano(fp, esercizi)) != NULL) {
    inserisciInListaPiano(p, ep);
  }
  return p;
}

void aggiornaEsercizioInPiano(esList_t p, esArray_t esercizi) {
  eserPiano_t *ep;
  int deletion = 0;
  printf("Inserire nome set rip (impostare valori a zero per cancellare): ");
  if ((ep = leggiEsPiano(stdin, esercizi)) == NULL) {
    return;
  }
  linkPiano iter = NULL, prev = NULL;
  for(iter = p->head, prev = NULL; iter != NULL; prev = iter, iter = iter->next) {
    if (iter->p->es == ep->es) {
      iter->p->set = ep->set;
      iter->p->rip = ep->rip;

      if (iter->p->set <= 0 || iter->p->rip <= 0) {
        deletion = 1;
        // Eliminazione dell'esercizio
        if (iter == p->head && iter == p->tail) {
            p->head = p->tail = NULL;
        } else if (iter == p->head) {
          p->head = iter->next;
        } else if (iter == p->tail) {
          p->tail = prev;
          prev->next = NULL;
        } else {
           prev->next = iter->next;
        }
        free(iter);
      }

      break;
    }
  }
  if (!deletion && iter == NULL) {
    // Aggiunge nuovo esercizio
    inserisciInListaPiano(p, ep);
  }
  stampaPiano(stdout, esercizi, p);
}

void freePiano(esList_t p) {
  linkPiano iter = p->head, toBeDeleted = NULL;

  if (p == NULL)
    return;

  while(iter) {
    toBeDeleted = iter;
    iter = iter->next;
    free(toBeDeleted);
  }
}

