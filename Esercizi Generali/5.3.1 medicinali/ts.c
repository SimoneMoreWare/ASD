#include <stdlib.h>
#include <string.h>
#include "ts.h"

struct tabella {char **vettore; int maxN; int N;};

/* duplica una stringa mediante allocazione dinamica */
/* fatta per illustrare una possibile realizzazione della strdup, che
   pur presente in molte librerie C, e utilizzabile tramite string.h, 
   non e' standard */
static char *strdupMia (char *s) {
  char *d = malloc (strlen (s) + 1);
  if (d == NULL) return NULL;
  strcpy (d,s);
  return d;
}

/* alloca tabella con puntatore a vettore, inizialmente vuoto: N=0 */
TS TScrea(int maxN) { 
  TS t = malloc(sizeof (struct tabella));
  t->vettore = (char **) malloc(maxN * sizeof (char *));
  t->maxN = maxN;
  t->N = 0;
  return t;
}

/* libera tabella: prima de-alloca le stringhe, poi il vettore, 
   infine la struct */
void TSlibera(TS t) {
  int id;
  for (id=0; id<t->N; id++) {
    free(t->vettore[id]);
  }
  free(t->vettore);
  free(t);
}

/* indica quanti simboli sono effettivamente presenti in tabella */
int TSdimensione(TS t) {
  return t->N;
}

/* aggiunge un simbolo senza controllare se si tratta di un duplicato */
int TSaggiungi(TS t, char *str) {
  int id = t->N;
  if (t->N >= t->maxN) return -1;
  t->vettore[id] = strdupMia(str);   
  t->N++;
  return id;
}

/* cerca mediante scansione lineare: se trova, ritorna l'indice */
int TScerca(TS t, char *str) {
  int id;
  for (id=0; id<t->N; id++) {
    if (strcmp(str,t->vettore[id])==0) return id;
  }
  return -1;
}

/* aggiunge senza duplicati. Cerca il simbolo. Se esiste in tabella, 
   ne ritorna l'indice, altrimenti lo aggiunge alla tabella */
int TScercaOAggiungi(TS t, char *str) {
  int id = TScerca(t,str);
  if (id>=0) return id;
  else return TSaggiungi(t,str);
}


char *TSleggiIndice(TS t, int id) {
  if (id < 0 || id>=t->N) return NULL;
  else return (t->vettore[id]);
}
