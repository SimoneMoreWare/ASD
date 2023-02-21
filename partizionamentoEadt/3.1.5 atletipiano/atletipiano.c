#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 50
#define N_SCELTE 11
#define DBG 1

enum { falso, vero };

typedef struct esercizio_s {
  char *nomeEs;
  char *tipoEs;
  char *catEs;
} esercizio_t;

typedef struct esercizi_s {
  int nEsercizi;
  int dimVett;
  esercizio_t *ve;
} tabEser;

typedef struct eserPiano_s {
  int set, rip;
  esercizio_t *es;
} eserPiano_t;

typedef struct nodoPiano_s *linkPiano;
typedef struct nodoPiano_s {
  eserPiano_t p;
  linkPiano next;
} nodoPiano_t;

typedef struct data_s{
  int giorno;
  int mese;
  int anno;
} data_t;

typedef struct categoria_s {
  char* nome;
} categoria_t;

typedef struct atleta_s {
  char* codice;
  char* cognome;
  char* nome;
  int categoria;
  data_t data;
  int ore;
  linkPiano head, tail;
} atleta_t;

typedef struct nodoAtleta_s *linkAtleta;
typedef struct nodoAtleta_s {
  atleta_t a;
  linkAtleta next;
} nodoAtleta_t;

typedef struct atleti_s {
  int nAtleti;
  linkAtleta head, tail;
} tabAtleti;

typedef struct categorie_s {
  int nCategorie;
  int dimVett;
  categoria_t *vc;
} categorie_t;

typedef int bool;

int comparaData(data_t d1, data_t d2);
int leggiAtleta(FILE *fp, atleta_t *a, categorie_t *categorie);
void stampaAnagrafica(tabAtleti *atleti, categorie_t *categorie, char* file); /*char* file = NULL per stampare sullo stdout */
void stampaEsercizi(tabEser *esercizi, char* file); /*char* file = NULL per stampare sullo stdout */
void caricaAnagrafica(tabAtleti *atleti, categorie_t *categorie);
void caricaEsercizi(tabEser *esercizi);
void stampaMenu(char *scelte[], int *selezione);
void parsificaData(char strData[], data_t *data);
void stampaAtleta(atleta_t atleta, categorie_t *categorie, FILE *fp);
void stampaPerCategoria(tabAtleti *atleti, categorie_t *categorie);
void ricercaCognome(tabAtleti *atleti, categorie_t *categorie, char* cognome, int nCharConfronto);
int ricercaCodice(tabAtleti *atleti, char *codice, atleta_t *a);
int ricercaCodiceModifica(tabAtleti *atleti, char *codice, int nuoveOre);
int ricercaCodiceCaricaPiano(tabAtleti *atleti, tabEser *esercizi, char *codice);
void aggiungi(tabAtleti *atleti, categorie_t *categorie);
void caricaPiano(char *codice, linkPiano *head, linkPiano *tail, tabEser *esercizi);
void stampaPiano(FILE *fp, linkPiano p);
void aggiornaEsercizioInPiano(linkPiano p);
void elimina(tabAtleti *atleti, char* codice);

int main(int argc, char** argv) {

  char *scelte[] = {
		"Uscita",
		"Stampa atleti a video",
		"Stampa atleti su file",
		"Stampa per categoria",
		"Aggiorna monte ore",
		"Ricerca per codice",
		"Ricerca per cognome",
		"Elimina atleta",
		"Aggiungi atleta",
        "Carica/Salva piano",
        "Modifica piano"
	};

  char nomeFile[25], codiceRicerca[LEN], cognomeRicerca[LEN];
  int selezione, nCharConfronto, nuoveOre;
  bool fineProgramma;
  atleta_t a;

  tabAtleti *atleti = calloc(1, sizeof(tabAtleti));
  categorie_t *categorie = calloc(1, sizeof(categorie_t));
  tabEser *esercizi = calloc(1, sizeof(tabEser));

  caricaAnagrafica(atleti, categorie);
#if DBG
  stampaAnagrafica(atleti, categorie, NULL);
#endif
  caricaEsercizi(esercizi);
#if DBG
  stampaEsercizi(esercizi, NULL);
#endif
  fineProgramma = falso;

  do {
		stampaMenu(scelte, &selezione);
		switch(selezione){

			case 0: {
				fineProgramma = vero;
		    } break;

			case 1: {
				stampaAnagrafica(atleti, categorie, NULL);
			} break;

			case 2: {
				printf("Inserire nome file\n");
				scanf("%s",nomeFile);
				stampaAnagrafica(atleti, categorie, nomeFile);
			} break;

			case 3: {
				printf("Stampa per categoria\n");
				stampaPerCategoria(atleti, categorie);
			} break;

			case 4: {
				printf("Inserire codice atleta: ");
				scanf("%s", codiceRicerca);
                printf("Inserire il nuovo monte ore settimanale: ");
				scanf("%d", &nuoveOre);
				if(ricercaCodiceModifica(atleti, codiceRicerca, nuoveOre) != 0)
                  printf("Monte ore di %s modificato\n", codiceRicerca);
				else
                  printf("Atleta non presente in elenco\n");
			} break;

			case 5: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
                if(ricercaCodice(atleti, codiceRicerca, &a) != 0)
				  stampaAtleta(a, categorie, stdout);
			} break;

			case 6:{
				printf("Inserire cognome atleta: ");
				scanf("%s%n", cognomeRicerca, &nCharConfronto);
				ricercaCognome(atleti, categorie, cognomeRicerca, nCharConfronto-1);
			} break;

			case 7: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				elimina(atleti, codiceRicerca);
			} break;

			case 8: {
				aggiungi(atleti, categorie);
			} break;

			case 9: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
                ricercaCodiceCaricaPiano(atleti, esercizi, codiceRicerca);
			} break;

			case 10: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
                if(ricercaCodice(atleti, codiceRicerca, &a) != 0) {
                if (a.head == NULL)
                  printf("Nessun piano disponibile");
                else
                  aggiornaEsercizioInPiano(a.head);
				}
			} break;

			default:{
				printf("Scelta non valida\n");
			} break;
		}
	} while(!fineProgramma);
	return 0;
}

void stampaMenu(char *scelte[], int *selezione){
  int i=0;

  printf("\nMENU'\n");
  for(i=0;i<N_SCELTE;i++)
    printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}

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
      if ( k == categorie->nCategorie) { /* categoria non trovata (primo elemento per tale categoria) */
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
  linkAtleta n;

  n = calloc(1, sizeof(*n));
  if (n == NULL)
    return NULL;
  n->a = a;
  n->next = next;
  return n;
}

void inserisciInListaAtleti(tabAtleti *atleti, atleta_t a) {
  linkAtleta toAdd;

  toAdd = newNodoAtleta(a, NULL);
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
  FILE *fp;
  atleta_t a;

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

void stampaAtleta(atleta_t a, categorie_t *categorie, FILE *fp) {
  fprintf(fp, "%s, %s %s, %s, %d/%d/%d, %d\n", a.codice, a.cognome, a.nome, categorie->vc[a.categoria].nome, a.data.giorno, a.data.mese, a.data.anno, a.ore);
  if (a.head != NULL)
    stampaPiano(stdout, a.head);
}

void stampaAnagrafica(tabAtleti *atleti, categorie_t *categorie, char* file) {
  linkAtleta iter = NULL;
  FILE *fp;

  if(file == NULL)
    fp = stdout;
  else
    fp = fopen(file,"w");

  for(iter = atleti->head;iter != NULL; iter=iter->next)
    stampaAtleta(iter->a, categorie, fp);

  if(file!=NULL)
    fclose(fp);
}

void stampaPerCategoria(tabAtleti *atleti, categorie_t *categorie){
  linkAtleta iter;
  int i;

  for(i=0;i<categorie->nCategorie;i++){
	printf("\nNome Categoria: %s\n",categorie->vc[i].nome);
	for(iter = atleti->head; iter != NULL; iter=iter->next) {
      if (iter->a.categoria == i)
		stampaAtleta(iter->a, categorie, stdout);
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

  for(iter = atleti->head; iter != NULL; iter=iter->next) {
    if (strncmp(iter->a.cognome, cognome, len) == 0) stampaAtleta(iter->a, categorie, stdout);
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

  for(i=0;i<esercizi->nEsercizi;i++) {
    stampaEsercizio(esercizi->ve[i]);
  }

  if(file!=NULL)
    fclose(fp);
}

esercizio_t* cercaEsercizio(char *esercizio, tabEser *esercizi) {
  int i;
  for(i=0;i<esercizi->nEsercizi;i++)
    if(!strcmp(esercizio, esercizi->ve[i].nomeEs))
      return &esercizi->ve[i];
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

  for(iter = p; iter != NULL; iter = iter->next) {
    fprintf(fp, "%s %d %d\n", iter->p.es->nomeEs, iter->p.set, iter->p.rip);
  }
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
	if (n == NULL) return NULL;
	n->p = p;
	n->next = next;
	return n;
}

void inserisciInListaPiano(linkPiano *head, linkPiano *tail, eserPiano_t p) {
	linkPiano toAdd = newNodoPiano(p, NULL);
	if (toAdd == NULL) return;
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

  while(leggiEsPiano(in, &e, esercizi) != 0) {
    inserisciInListaPiano(head, tail, e);
  }

#if DBG
  printf("Piano per %s\n", codice);
  stampaPiano(stdout, *head);
#endif /* DBG */
}

void aggiornaEsercizioInPiano(linkPiano p) {
  char nomeTmp[LEN];
  int set, rip;
  linkPiano iter = NULL;

  printf("Inserire nome set rip: ");
  scanf("%s %d %d", nomeTmp, &set, &rip);
  for(iter = p; iter != NULL; iter = iter->next) {
    if (strcmp(nomeTmp, iter->p.es->nomeEs) == 0) {
      iter->p.set = set;
      iter->p.rip = rip;
      break;
    }
  }
  if (iter == NULL) printf("Impossibile modificare\n");
  stampaPiano(stdout, p);
}
