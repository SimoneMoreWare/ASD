#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 26
#define N_SCELTE 9
#define DBG 1

typedef enum chiaveOrdinamento_e {NESSUNO, DATA_NASCITA, CODICE, COGNOME} chiaveOrdinamento;

enum { falso, vero };

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
} atleta_t;

typedef struct nodo_s *link;
typedef struct nodo_s {
  atleta_t *a;
  link next;
} nodo_t;

typedef struct categorie_s {
  int nCategorie;
  int dimVett;
  categoria_t *vc;
} categorie_t;

typedef int bool;

int comparaData(data_t d1, data_t d2);
atleta_t *leggiAtleta(FILE *fp, categorie_t *categorie);
void stampaAnagrafica(link headAtleti, categorie_t *categorie, char* file); /* char* file = NULL per stampare sullo stdout */
void caricaAnagrafica(link *headAtleti, link *tailAtleti, categorie_t *categorie);
void stampaMenu(char *scelte[], int *selezione);
void parsificaData(char strData[], data_t *data);
void stampaAtleta(atleta_t *atleta, categorie_t *categorie, FILE *fp);
void stampaPerCategoria(link headAtleti, categorie_t *categorie);
void ricercaCognome(link headAtleti, categorie_t *categorie, char* cognome, int nCharConfronto);
void ricercaCodice(link headAtleti, char* codice, atleta_t **pa);
void elimina(link *headAtleti, link *tailAtleti, char* codice);
void aggiungi(link *headAtleti, link *tailAtleti, categorie_t *categorie);


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
		"Aggiungi atleta"
	};

  char codiceRicerca[LEN], cognomeRicerca[LEN];
  char nomeFile[25];
  int selezione, nCharConfronto;
  link headAtleti = NULL, tailAtleti = NULL;
  categorie_t *categorie = calloc(1, sizeof(categorie_t));
  bool fineProgramma = falso;
  atleta_t *pa;

  caricaAnagrafica(&headAtleti, &tailAtleti, categorie);
#if DBG
  stampaAnagrafica(headAtleti, categorie, NULL);
#endif

  do {
		stampaMenu(scelte, &selezione);
		switch(selezione){

			case 0: {
				fineProgramma = vero;
		   } break;

			case 1: {
				stampaAnagrafica(headAtleti, categorie, NULL);
			} break;

			case 2: {
				printf("Inserire nome file\n");
				scanf("%s",nomeFile);
				stampaAnagrafica(headAtleti, categorie, nomeFile);
			} break;

			case 3: {
				printf("Stampa per categoria\n");
				stampaPerCategoria(headAtleti, categorie);
			} break;

			case 4: {
				printf("Inserire codice atleta: ");
				scanf("%s", codiceRicerca);
				ricercaCodice(headAtleti, codiceRicerca, &pa);
				if(pa != NULL) {
					printf("Inserire il nuovo monte ore settimanale: ");
					scanf("%d", &pa->ore);
				}
				else
					printf("Atleta non presente in elenco\n");
			} break;

			case 5: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				ricercaCodice(headAtleti, codiceRicerca, &pa);
				if(pa != NULL) {
				  stampaAtleta(pa, categorie, stdout);
				}
			} break;

			case 6:{
				printf("Inserire cognome atleta: ");
				scanf("%s%n", cognomeRicerca, &nCharConfronto);
				ricercaCognome(headAtleti, categorie, cognomeRicerca, nCharConfronto-1);
			} break;

			case 7: {
				printf("Inserire codice: ");
				scanf("%s", codiceRicerca);
				elimina(&headAtleti, &tailAtleti, codiceRicerca);
			} break;

			case 8: {
				aggiungi(&headAtleti, &tailAtleti, categorie);
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
	for(i=0;i<N_SCELTE;i++) printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}

atleta_t *leggiAtleta(FILE *fp, categorie_t *categorie) {
  char codiceTmp[LEN], nomeTmp[LEN], cognomeTmp[LEN], categoriaTmp[LEN], dataTmp[LEN];
  int k, ore;
  atleta_t *a;
  if (fscanf(fp, "%s %s %s %s %s %d", codiceTmp, cognomeTmp, nomeTmp, categoriaTmp, dataTmp, &ore) == 6) {
	a = calloc(1, sizeof(atleta_t));
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
	return a;
  }
  return NULL;
}

link newNode(atleta_t *a, link next) {
	link n = calloc(1, sizeof(*n));
	if (n == NULL)
        return NULL;
	n->a = a;
	n->next = next;
	return n;
}

void insertTail(link *headAtleti, link *tailAtleti, atleta_t *a) {
	link toAdd = newNode(a, NULL);
	if (toAdd == NULL) return;
    if(*headAtleti == NULL) {
      *headAtleti = *tailAtleti = toAdd;
    } else {
      (*tailAtleti)->next = toAdd;
      *tailAtleti = toAdd;
    }

}

void caricaAnagrafica(link *headAtleti, link *tailAtleti, categorie_t *categorie){
  FILE *fp;
  atleta_t *a = NULL;
  int n;

  fp = fopen("atleti.txt","r");

  if(fp == NULL) {
		printf("Errore nell'apertura del file\n ");
		exit(-1);
  }

  categorie->vc = calloc(1, sizeof(categoria_t));
  categorie->nCategorie = 0;
  categorie->dimVett = 1;

  fscanf(fp, "%d", &n);

  while((a = leggiAtleta(fp, categorie)) != NULL) {
	insertTail(headAtleti, tailAtleti, a);
  }
  fclose(fp);
}

void aggiungi(link *headAtleti, link *tailAtleti, categorie_t *categorie){
  atleta_t *a;

  printf("Cod Cogn Nome Cat Data Ore: ");
  a = leggiAtleta(stdin, categorie);
  if (a != NULL)
    insertTail(headAtleti, tailAtleti, a);
}

void parsificaData(char strData[], data_t *data) {
	sscanf(strData, "%d/%d/%d", &data->giorno, &data->mese, &data->anno);
}

void stampaAtleta(atleta_t *p, categorie_t *categorie, FILE *fp) {
  fprintf(fp, "%s, %s %s, %s, %d/%d/%d, %d\n", p->codice, p->cognome, p->nome, categorie->vc[p->categoria].nome, p->data.giorno, p->data.mese, p->data.anno, p->ore);
}

void stampaAnagrafica(link headAtleti, categorie_t *categorie, char* file) {
  link iter = NULL;
  FILE *fp;
  if(file == NULL)
      fp = stdout;
  else
      fp = fopen(file,"w");

  for(iter = headAtleti;iter != NULL; iter=iter->next) {
    stampaAtleta(iter->a, categorie, fp);
  }

  if(file!=NULL)
    fclose(fp);
}

void stampaPerCategoria(link headAtleti, categorie_t *categorie){
	int i;
    link iter;

	for(i=0;i<categorie->nCategorie;i++){
		printf("\nNome Categoria: %s\n",categorie->vc[i].nome);
		for(iter = headAtleti; iter != NULL; iter=iter->next) {
      if (iter->a->categoria == i)
			stampaAtleta(iter->a, categorie, stdout);
		}
	}
}

void ricercaCodice(link headAtleti, char* codice, atleta_t **pa){
  link iter;
  for(iter = headAtleti; iter != NULL; iter=iter->next) {
    if (strcmp(iter->a->codice, codice) == 0) {
		*pa = iter->a;
		return;
	}
  }
  *pa = NULL;
}

void freeAtleta(atleta_t *a) {
  if (a == NULL)
    return;
  free(a->codice);
  free(a->nome);
  free(a->cognome);
  free(a);
}

void elimina(link *headAtleti, link *tailAtleti, char* codice){
  link iter, prev;
  for(iter = *headAtleti, prev = NULL; iter != NULL; prev = iter, iter=iter->next) {
    if (strcmp(iter->a->codice, codice) == 0) {
	  if (iter == *headAtleti && iter == *tailAtleti) {
		  *headAtleti = *tailAtleti = NULL;
	  } else if (iter == *headAtleti) {
		*headAtleti = iter->next;
	  } else if (iter == *tailAtleti) {
		*tailAtleti = prev;
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

void ricercaCognome(link headAtleti, categorie_t *categorie, char* cognome, int nCharConfronto){
  link iter;
  int len = strlen(cognome);
  for(iter = headAtleti; iter != NULL; iter=iter->next) {
    if (strncmp(iter->a->cognome, cognome, len) == 0) stampaAtleta(iter->a, categorie, stdout);
  }
}
