#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 26
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

typedef struct atleti_s {
  int nAtleti;
  atleta_t *va;
  atleta_t **dob, **cod, **cogn;
} atleti_t;

typedef struct categorie_s {
  int nCategorie;
  int dimVett;
  categoria_t *vc;
} categorie_t;

typedef int bool;

typedef enum sceltaMenu_e {
  uscita_c, stampa_video_c, stampa_file_c, ordina_data_c, ordina_cod_c,
  ordina_cogn_c, ordina_cat_c, aggiorna_ore_c, cerca_cod_c, cerca_cogn_c, numScelte_c
} sceltaMenu;

/* si propone una tabella di conversione tra menu e stringhe, basata su
   vettore di struct, anziche' vettore con accesso diretto */
struct {sceltaMenu codice; char *prompt; char *comando;} scelte[] = {
  {uscita_c, "Uscita", "Fine"},
  {stampa_video_c, "Stampa atleti a video", "Video"},
  {stampa_file_c, "Stampa atleti su file", "File"},
  {ordina_data_c, "Ordina per data di nascita", "Od"},
  {ordina_cod_c, "Ordina per codice atleta", "Ocod"},
  {ordina_cogn_c, "Ordina per cognome", "Ocogn"},
  {ordina_cat_c, "Ordina per categoria", "Ocat"},
  {aggiorna_ore_c, "Aggiorna monte ore", "Ore"},
  {cerca_cod_c, "Ricerca per codice", "Codice"},
  {cerca_cogn_c, "Ricerca per cognome", "Cognome"},
  {numScelte_c, NULL, NULL}
};

int comparaData(data_t d1, data_t d2);
void stampaAnagrafica(atleti_t *atleti, categorie_t *categorie, chiaveOrdinamento key, char* file); /*char* file = NULL per stampare sullo stdout */
void caricaAnagrafica(FILE *fin, atleti_t *atleti, categorie_t *categorie);
sceltaMenu menu(void);
void parsificaData(char strData[], data_t *data);
void stampaAtleta(atleta_t *atleta, categorie_t *categorie, FILE *fp);
void stampaPerCategoria(atleti_t *atleti, categorie_t *categorie);
void ordinaStabile(atleta_t **atleti, int na, chiaveOrdinamento k);
void ricercaCognomeDicotomica(atleti_t *atleti, categorie_t *categorie, char* cognome, int nCharConfronto);
bool ricercaCodiceDicotomica(atleti_t *atleti, char* codice, int *indiceAtleta);
void libera(atleti_t *atleti, categorie_t *categorie);

int main(int argc, char** argv) {

  char codiceRicerca[LEN], cognomeRicerca[LEN];
  sceltaMenu selezione;
  int nCharConfronto;
  atleti_t *atleti = calloc(1, sizeof(atleti_t));
  categorie_t *categorie = calloc(1, sizeof(categorie_t));
  bool fineProgramma;
  char nomeFile[25];
  int indiceAtleta = -1, trovato = 0;
  FILE *fp;
  fp = fopen("atleti.txt","r");

  if(fp == NULL) {
    printf("Errore nell'apertura del file\n ");
    exit(-1);
  }

  caricaAnagrafica(fp, atleti, categorie);
#if DBG
  stampaAnagrafica(atleti, categorie, NESSUNO, NULL);
#endif
  fineProgramma = falso;
  fclose(fp);
  do {
    selezione = menu();
    switch(selezione){

    case uscita_c:
      fineProgramma = vero;
    break;

    case stampa_video_c:
      stampaAnagrafica(atleti, categorie, NESSUNO, NULL);
      break;

    case stampa_file_c:
      printf("Inserire nome file\n");
      scanf("%s",nomeFile);
      stampaAnagrafica(atleti, categorie, NESSUNO, nomeFile);
      break;

    case ordina_data_c:
      printf("Elenco atleti ordinato per data di nascita\n");
      stampaAnagrafica(atleti, categorie, DATA_NASCITA, NULL);
      break;

    case ordina_cod_c:
      printf("Elenco atleti ordinato per codice atleta\n");
      stampaAnagrafica(atleti, categorie, CODICE, NULL);
      break;

    case ordina_cogn_c:
      printf("Elenco atleti ordinato per cognome\n");
      stampaAnagrafica(atleti, categorie, COGNOME, NULL);
      break;

    case ordina_cat_c:
      printf("Stampa per categoria\n");
      stampaPerCategoria(atleti, categorie);
      break;

    case aggiorna_ore_c:
      printf("Inserire codice atleta: ");
      scanf("%s", codiceRicerca);
      indiceAtleta = -1;
      trovato = ricercaCodiceDicotomica(atleti, codiceRicerca, &indiceAtleta);
      if(trovato) {
	printf("Inserire il nuovo monte ore settimanale: ");
	scanf("%d", &atleti->va[indiceAtleta].ore);
      }
      else
	printf("Atleta non presente in elenco\n");
      break;

    case cerca_cod_c:
      printf("Inserire codice: ");
      scanf("%s", codiceRicerca);
      indiceAtleta = -1;
      if(ricercaCodiceDicotomica(atleti, codiceRicerca, &indiceAtleta)) {
	stampaAtleta(&(atleti->va[indiceAtleta]), categorie, stdout);
      }
      break;

    case cerca_cogn_c:
      printf("Inserire cognome atleta: ");
      scanf("%s%n", cognomeRicerca, &nCharConfronto);
      ricercaCognomeDicotomica(atleti, categorie, cognomeRicerca, nCharConfronto-1);
      break;

    default:
      printf("Scelta non valida\n");
      break;
    }
  } while(!fineProgramma);
  libera(atleti, categorie);
  free(atleti);
  free(categorie);
  return 0;
}

int comparaData(data_t d1, data_t d2) {
  if (d1.anno != d2.anno)
    return (d1.anno-d2.anno);
  else if (d1.mese != d2.mese)
    return (d1.mese-d2.mese);
  else if (d1.giorno != d2.giorno)
    return (d1.giorno-d2.giorno);
  else return 0;
}

sceltaMenu menu(void){
  int i, nTrovate, iTrovata, len;
  char scelta[LEN];
  printf("\nMENU'\n");
  for(i=0; i<numScelte_c; i++)
    printf("%s (%s)\n", scelte[i].prompt, scelte[i].comando);
  printf("\nFAI UNA SCELTA: ");
  scanf(" %s",scelta);
  iTrovata = -1;
  nTrovate = 0;
  len = strlen(scelta);
  for(i=0; i<numScelte_c; i++) {
    if (strncmp(scelta,scelte[i].comando,len)==0) {
      nTrovate++;
      iTrovata = i;
    }
  }
  if (nTrovate==1) {
    return scelte[iTrovata].codice;
  }
  else if (nTrovate>1) {
    printf("Scelta %s ambigua\n", scelta);
  }
  return numScelte_c;
}


void caricaAnagrafica(FILE *fin, atleti_t *atleti, categorie_t *categorie){
  char codiceTmp[LEN], nomeTmp[LEN], cognomeTmp[LEN], categoriaTmp[LEN], dataTmp[LEN];
  int i, k;

  fscanf(fin, "%d", &atleti->nAtleti);

  if (atleti->nAtleti <= 0) {
		printf("Errore nella dimensione del atleti\n");
		exit(-1);
	};

  atleti->va = calloc((atleti->nAtleti), sizeof(atleta_t));
  categorie->vc = calloc(1, sizeof(categoria_t));
  categorie->nCategorie = 0;
  categorie->dimVett = 1;

  for(i=0;i<atleti->nAtleti;i++) {
    fscanf(fin, "%s %s %s %s", codiceTmp, cognomeTmp, nomeTmp, categoriaTmp);
  	atleti->va[i].codice = strdup(codiceTmp);
    atleti->va[i].cognome = strdup(cognomeTmp);
    atleti->va[i].nome = strdup(nomeTmp);

    /* Gestione categoria */
    {
      k=0;
      while (k < categorie->nCategorie && strcmp(categorie->vc[k].nome, categoriaTmp) != 0)
        k++;
      if ( k == categorie->nCategorie) { /*categoria non trovata (primo elemento per tale categoria)*/
        if (categorie->nCategorie == categorie->dimVett) {
          categorie->dimVett *= 2;
          categorie->vc = realloc (categorie->vc, categorie->dimVett*sizeof(categoria_t));
        }
        categorie->vc[k].nome = strdup(categoriaTmp);
        categorie->nCategorie++;
      }
      atleti->va[i].categoria = k;
    }

    fscanf(fin,"%s",dataTmp);
    parsificaData(dataTmp, &atleti->va[i].data);
    fscanf(fin,"%d",&atleti->va[i].ore);
  }

  atleti->cod = calloc(atleti->nAtleti, sizeof(atleta_t*));
  atleti->cogn = calloc(atleti->nAtleti, sizeof(atleta_t*));
  atleti->dob = calloc(atleti->nAtleti, sizeof(atleta_t*));

  for(i=0;i<atleti->nAtleti;i++) {
    atleti->dob[i] = &atleti->va[i];
    atleti->cod[i] = &atleti->va[i];
    atleti->cogn[i] = &atleti->va[i];
  }

  ordinaStabile(atleti->dob, atleti->nAtleti, DATA_NASCITA);
  ordinaStabile(atleti->cod, atleti->nAtleti, CODICE);
  ordinaStabile(atleti->cogn, atleti->nAtleti, COGNOME);

}

void parsificaData(char strData[], data_t *data) {
	sscanf(strData, "%d/%d/%d", &data->giorno, &data->mese, &data->anno);
}

void stampaAtleta(atleta_t *p, categorie_t *categorie, FILE *fp) {
  fprintf(fp, "%s, %s %s, %s, %d/%d/%d, %d\n", p->codice, p->cognome, p->nome, categorie->vc[p->categoria].nome, p->data.giorno, p->data.mese, p->data.anno, p->ore);
}

void stampaAnagrafica(atleti_t *atleti, categorie_t *categorie, chiaveOrdinamento key, char* file) {
  FILE *fp;
  int i;
  if(file == NULL)
      fp = stdout;
  else
      fp = fopen(file,"w");

  switch(key) {
  case CODICE:
    for(i=0; i<atleti->nAtleti; i++) stampaAtleta((atleti->cod[i]), categorie, fp);
    break;
  case DATA_NASCITA:
    for(i=0; i<atleti->nAtleti; i++) stampaAtleta((atleti->dob[i]), categorie, fp);
    break;
  case COGNOME:
    for(i=0; i<atleti->nAtleti; i++) stampaAtleta((atleti->cogn[i]), categorie, fp);
  break;
  default:
    for(i=0; i<atleti->nAtleti; i++) stampaAtleta(&(atleti->va[i]), categorie, fp);
  }

  if(file!=NULL)
    fclose(fp);
}

int cerca(atleti_t *atleti, int start, chiaveOrdinamento k) {
  int j, min = start;
  for(j=start+1;j<atleti->nAtleti;j++) {
    switch(k) {
    case DATA_NASCITA: {
      if(comparaData(atleti->va[min].data, atleti->va[j].data) > 0) min = j;
    } break;
    case CODICE: {
      if(strcmp(atleti->va[min].codice, atleti->va[j].codice) > 0) min = j;
    } break;
    case COGNOME: {
      int cmp = strcmp(atleti->va[min].cognome, atleti->va[j].cognome);
      if (cmp == 0) cmp = strcmp(atleti->va[min].nome, atleti->va[j].nome);
      if(cmp > 0) min = j;
    } break;
    default: {
    } break;
    }
  }
  return min;
}

int confrontaAtleti(atleta_t *a1, atleta_t *a2, chiaveOrdinamento k) {
  int cmp;
  switch(k) {
    case DATA_NASCITA:
      return comparaData(a1->data, a2->data);
    case CODICE:
      return strcmp(a1->codice, a2->codice);
    case COGNOME:
      cmp = strcmp(a1->cognome, a2->cognome);
      if (cmp == 0) cmp = strcmp(a1->nome, a2->nome);
      return cmp;
    default:
      break;
  }
  return 0;
}

void ordinaStabile(atleta_t **vpa, int na, chiaveOrdinamento k) {
  int i, j;
  int l = 0, r = na-1;
  atleta_t *x;

  for(i=l+1;i<=r;i++) {
    x = vpa[i];
    j = i-1;
    while(j>=l && confrontaAtleti(x, vpa[j], k) < 0) {
      vpa[j+1] = vpa[j];
      j--;
    }
    vpa[j+1] = x;
  }
}

void stampaPerCategoria(atleti_t *atleti, categorie_t *categorie){
  int i,j;
  for(i=0;i<categorie->nCategorie;i++){
    printf("\nNome Categoria: %s\n",categorie->vc[i].nome);
    for(j=0;j<atleti->nAtleti;j++) {
      if (atleti->va[j].categoria == i)
	stampaAtleta(&(atleti->va[j]), categorie, stdout);
    }
  }
}

bool ricercaCodiceDicotomica(atleti_t *atleti, char* codice, int *indiceAtleta){
  int iniziale = 0, finale = atleti->nAtleti - 1, medio, cmp;
  atleta_t **vpa;

  if(finale < 0)
    return falso;

  vpa = atleti->cod;

  while(iniziale <= finale) {
    medio = (iniziale + finale) / 2;
    cmp = strcmp(vpa[medio]->codice, codice);
    if(cmp == 0) {
      *indiceAtleta = medio;
      return vero;
    }
    if(cmp < 0)
      iniziale = medio + 1;
    else
      finale = medio - 1;
  }
  return falso;
}

void ricercaCognomeDicotomica(atleti_t *atleti, categorie_t *categorie, char* cognome, int nCharConfronto){
  int iniziale = 0, finale = atleti->nAtleti - 1, medio, i, j, cmp;
  bool trovato = falso;
  atleta_t **vpa;

  vpa = atleti->cogn;

  while(iniziale <= finale && !trovato) {
    medio = (iniziale + finale) / 2;
    cmp = strncmp(vpa[medio]->cognome, cognome, nCharConfronto);
    if(cmp == 0) {
      trovato = vero;
    } else {
      if(cmp < 0)
	iniziale = medio + 1;
      else
	finale = medio - 1;
    }
  }

  if(trovato) {
    i = medio;
    j = medio -1;
    while(i < atleti->nAtleti && strncmp(vpa[i]->cognome, cognome, nCharConfronto) == 0) {
      stampaAtleta(vpa[i], categorie, stdout);
      i++;
    }
    while(j>=0 && strncmp(vpa[j]->cognome, cognome, nCharConfronto) == 0) {
      stampaAtleta(vpa[j], categorie, stdout);
      j--;
    }
  }
  else
    printf("Atleta non trovato");
}

void libera(atleti_t *atleti, categorie_t *categorie) {
  int i;
  for(i=0;i<atleti->nAtleti;i++) {
    free(atleti->va[i].cognome);
    free(atleti->va[i].nome);
    free(atleti->va[i].codice);
  }
  for(i=0;i<categorie->nCategorie;i++) {
    free(categorie->vc[i].nome);
  }
  free(atleti->cod);
  free(atleti->cogn);
  free(atleti->dob);
  free(atleti->va);
  free(categorie->vc);
}



