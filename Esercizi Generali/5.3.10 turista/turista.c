#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DBG 0
#define BUDGET_SINGLE 200
#define BUDGET_TOTAL  800

/********************************************************************
  Strutture dati utilizzate
********************************************************************/

typedef struct museo museo_t;
typedef struct arco arco_t;
typedef struct nodo nodo_t;

/* struttura per la descrizione delle attrazioni */
struct museo {
  char *nome;
  int prezzo;
  int stelle;
  int visto;
  int visitato;
  museo_t *next;
};

/* struttura per la descrizione degli archi */
struct arco {
  nodo_t *dst;
  int costo;
  arco_t *next;
};

/* struttura per la descrizione dei nodi */
struct nodo {
  char *nome;
  int visto;
  arco_t *archi;
  museo_t *musei;
  nodo_t *next;
};

/********************************************************************
  Prototipi
********************************************************************/

nodo_t *leggi();
void separa(char *buffer);
nodo_t *trova(nodo_t **head_ptr, char *nome);
void visita(nodo_t *start);
int cicla(nodo_t *nodo, nodo_t *start, int budget, int stelle, int max,
	      arco_t *solCorr, arco_t **solBest);
arco_t *aggiornaSoluzione(arco_t *solCorr, arco_t *solBest);

/********************************************************************
  Main
********************************************************************/
int main()
{
  char nome[100];
  int stelle, costo;
  nodo_t *head, *ptr, *start;
  museo_t *museo, *aux;
  arco_t *edge, *tmp;

  head = leggi();
#if DBG
  /* stampa di debug */
  ptr = head;
  while (ptr != NULL) {
    edge = ptr->archi;
    while (edge != NULL) {
      printf("%s --> %s (%d)\n", ptr->nome, edge->dst->nome, edge->costo);
      edge = edge->next;
    }

    museo = ptr->musei;
    while (museo != NULL) {
      printf("%s: %s %d %d\n", ptr->nome, museo->nome, museo->stelle, museo->prezzo);
      museo = museo->next;
    }

    ptr = ptr->next;
  }
#endif

  printf("Citta' di partenza'? ");
  scanf("%s", nome);
  start = trova(&head, nome);

  /* trovo le citta' raggiungibili */
  visita(start);

  /* conto le stelle e il costo relativi */
  ptr = head;
  stelle = costo = 0;
  printf("Citta' e musei visitati:\n");
  while (ptr != NULL) {
    if (ptr->visto) {
      printf("- %s\n", ptr->nome);
      museo = ptr->musei;
      while (museo != NULL) {
	    costo += museo->prezzo;
	    stelle += museo->stelle;
	    printf("  - %s\n", museo->nome);
	    museo = museo->next;
      }
    }
    ptr = ptr->next;
  }
  printf("Stelle totali=%d, costo musei=%d\n\n", stelle, costo);

  /* determino il cammino ciclico ottimo */
  edge = NULL;
  cicla(start, start, BUDGET_TOTAL, 0, 0, NULL, &edge);
  stelle = costo = 0;
  printf("Cammino ciclico ottimo:\n");
  while (edge != NULL) {
    tmp = edge;
    ptr = edge->dst;
    costo += edge->costo;
    printf("- %s", ptr->nome);
    museo = ptr->musei;
    while (museo != NULL) {
      if (museo->visitato) {
	    costo += museo->prezzo;
	    stelle += museo->stelle;
	    museo->visitato = 0;
	    printf(" / %s", museo->nome);
	    break;
      }
      museo = museo->next;
    }
    printf("\n");
    edge = edge->next;
    free(tmp);
  }
  printf("Stelle totali=%d, costo totale=%d\n", stelle, costo);

  /* deallocazione della memoria */
  while (head != NULL) {
    ptr = head;
    museo = head->musei;
    while (museo != NULL) {
      aux = museo;
      museo = museo->next;
      free(aux->nome);
      free(aux);
    }
    edge = head->archi;
    while (edge != NULL) {
      tmp = edge;
      edge = edge->next;
      free(tmp);
    }
    head = head->next;
    free(ptr->nome);
    free(ptr);
  }
  return EXIT_SUCCESS;
}

/********************************************************************
  Funzione di lettura dei file di ingresso
********************************************************************/
nodo_t *leggi()
{
  char nome1[100], nome2[100], buffer[500];
  nodo_t *n1, *n2, *head=NULL;
  int costo, stelle;
  museo_t *museo;
  arco_t *edge;
  FILE *fp;

  fp = fopen("collegamenti.txt", "r");
  while (fgets(buffer, 500, fp) != NULL) {
    separa(buffer);
    sscanf(buffer, "%s %s %d", nome1, nome2, &costo);
    n1 = trova(&head, nome1);
    n2 = trova(&head, nome2);

    edge = (arco_t *)malloc(sizeof(arco_t));
    edge->costo = costo;
    edge->dst = n2;
    edge->next = n1->archi;
    n1->archi = edge;

    edge = (arco_t *)malloc(sizeof(arco_t));
    edge->costo = costo;
    edge->dst = n1;
    edge->next = n2->archi;
    n2->archi = edge;
  }
  fclose(fp);

  fp = fopen("attrazioni.txt", "r");
  while (fgets(buffer, 500, fp) != NULL) {
    separa(buffer);
    sscanf(buffer, "%s %s %d %d", nome1, nome2, &stelle, &costo);
    n2 = trova(&head, nome2);
    museo = (museo_t *)malloc(sizeof(museo_t));
    museo->nome = strdup(nome1);
    museo->stelle = stelle;
    museo->prezzo = costo;
    museo->visto = museo->visitato = 0;
    museo->next = n2->musei;
    n2->musei = museo;
  }
  fclose(fp);

  return head;
}

/********************************************************************
  Funzione di separazione dei campi (acquisiti come unica stringa)
********************************************************************/
void separa(char *buffer)
{
  int i;

  for (i=0; i<strlen(buffer); i++) {
    if (buffer[i]=='-' || buffer[i]==',') {
      buffer[i] = ' ';
    }
  }
}

/********************************************************************
  Funzione di ricerca/aggiunta di un nodo
********************************************************************/
nodo_t *trova(nodo_t **head_ptr, char *nome)
{
  nodo_t *ptr=*head_ptr;

  /* cerco se il vertice e' stato inserito */
  while (ptr != NULL) {
    if (strcmp(ptr->nome, nome) == 0) {
      return ptr;
    }
    ptr = ptr->next;
  }

  /* aggiungo un nuovo vertice */
  ptr = (nodo_t *)malloc(sizeof(nodo_t));
  ptr->nome = strdup(nome);
  ptr->musei = NULL;
  ptr->archi = NULL;
  ptr->visto = 0;
  ptr->next = *head_ptr;
  *head_ptr = ptr;
  return ptr;
}

/********************************************************************
  Funzione di visita del grafo (richiesta 1)
********************************************************************/
void visita(nodo_t *start)
{
  arco_t *edge;

  if (start->visto) {
    return;
  }

  start->visto = 1;
  edge = start->archi;
  while (edge != NULL) {
    if (edge->costo <= BUDGET_SINGLE) {
      visita(edge->dst);
    }
    edge = edge->next;
  }
}

/********************************************************************
  Funzione di calcolo del cammino ciclico (richiesta 2)
********************************************************************/
int cicla(nodo_t *nodo, nodo_t *start, int budget, int stelle, int max,
	      arco_t *solCorr, arco_t **solBest)
{
  museo_t *museo;
  arco_t *edge;

  /* aggiungo la citta' corrente al cammino temporaneo */
  edge = (arco_t *)malloc(sizeof(arco_t));
  edge->dst = nodo;
  edge->costo = 0;
  edge->next = solCorr;
  solCorr = edge;

  if (nodo == start) {
    /* controlla e salva la soluzione */
    if (max < stelle) {
      max = stelle;
      *solBest = aggiornaSoluzione(solCorr, *solBest);
    }
  }

  /* se possibile, visito un museo, poi ricorro sulle citta' adiacenti */
  museo = nodo->musei;
  while (museo != NULL) {
    if (museo->visto==0 && museo->prezzo<=budget) {
      budget -= museo->prezzo;
      stelle += museo->stelle;
      museo->visto = 1;

      edge = nodo->archi;
      while (edge != NULL) {
	    if (edge->costo <= budget) {
	      budget -= edge->costo;
	      solCorr->costo = edge->costo;
	      max = cicla(edge->dst, start, budget, stelle, max, solCorr, solBest);
	      budget += edge->costo;
        }
	    edge = edge->next;
      }

      budget += museo->prezzo;
      stelle -= museo->stelle;
      museo->visto = 0;
    }
    museo = museo->next;
  }

  /* ricorro sulle citta' adiacenti, senza visitare musei della citta' corrente */
  edge = nodo->archi;
  while (edge != NULL) {
    if (edge->costo <= budget) {
      budget -= edge->costo;
      solCorr->costo = edge->costo;
      max = cicla(edge->dst, start, budget, stelle, max, solCorr, solBest);
      budget += edge->costo;
    }
    edge = edge->next;
  }

  /* rimuovo la citta' corrente dal cammino temporaneo */
  free(solCorr);

  return max;
}

/********************************************************************
  Funzione di salvataggio della soluzione corrente
********************************************************************/
arco_t *aggiornaSoluzione(arco_t *solCorr, arco_t *solBest)
{
  arco_t *head, *tmp, *aux;
  museo_t *museo;

  /* elimino la soluzione ottima temporanea */
  head = solBest;
  while (head != NULL) {
    museo = head->dst->musei;
    while (museo != NULL) {
      museo->visitato = 0;
      museo = museo->next;
    }
    tmp = head->next;
    free(head);
    head = tmp;
  }

  /* copio la soluzione corrente nella soluzione ottima */
  head = solCorr;
  tmp = NULL;
  while (head != NULL) {
    museo = head->dst->musei;
    while (museo != NULL) {
      museo->visitato = museo->visto;
      museo = museo->next;
    }
    aux = (arco_t *)malloc(sizeof(arco_t));
    aux->dst = head->dst;
    aux->costo = head->costo;
    aux->next = tmp;
    tmp = aux;

    head = head->next;
  }

  return tmp;
}
