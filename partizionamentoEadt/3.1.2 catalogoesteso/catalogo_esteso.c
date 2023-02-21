#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXC 10
#define MAXS 25
#define MAXR 100 /* per input prodotto */

typedef struct {
  char codice[MAXC],*nome,*categoria;
  int quant;
  struct {
    int g,m,a;
  } data;
  float prezzo;
  int cancellato;
} prodotto_t;

typedef enum {
  co_stampa,co_aggiorna,co_aggiungi,co_ricerca,co_cancella,co_fine,co_err
} comando_t;
/* variabile globale messa accanto al tipo enum per mantenere allineamento */
char *comandi[co_err]={"stampa","aggiorna","aggiungi","ricerca","cancella","fine"};
typedef enum {
  cr_tutto,cr_categoria,cr_prezzoAsc,cr_prezzoDis,cr_codice,cr_nome,cr_nomeParziale,cr_err
} criterio_t;
/* variabile globale messa accanto al tipo enum per mantenere allinemaneto */
char *criteri[cr_err]={
  "tutto","categoria","prezzoAsc","prezzoDis","codice","nome","nomeParziale"
};
criterio_t crOrd[]={cr_categoria,cr_prezzoAsc,cr_prezzoDis,cr_codice,cr_nome,cr_err};

typedef struct {
  comando_t com;
  criterio_t crit;
  char altro[MAXR]; /* sovradimensionato per eventuali comandi lunghi */
} ComandoCompleto;

int leggiCatalogo(prodotto_t **catP, prodotto_t **rOrd[]);
void generaOrdini(prodotto_t *cat, prodotto_t **rOrd[], int np);
void ordinaRifCatalogo (prodotto_t **catR, int np, criterio_t crit);
void stampaProdotto(prodotto_t *p, FILE *fp);
void stampaCatalogo(prodotto_t *cat, prodotto_t **rOrd[], int np, FILE *f, criterio_t crit);
void stampaCategorie(prodotto_t *cat, int np, criterio_t crit);
ComandoCompleto leggiComando();
int confrontaProdotti (prodotto_t *a, prodotto_t *b, criterio_t crit);
void ordinaCatalogo (prodotto_t *cat, int np, criterio_t crit);
void ricercaStampa(prodotto_t **rOrd[], int np, char *s, criterio_t crit);
void aggiorna(prodotto_t **rOrd[], int np, char *s, criterio_t crit);
void aggiungiProdotto(prodotto_t **catP, prodotto_t **rOrd[], int *npp, int *maxpp, char *s);
void cancella(prodotto_t **rOrd[], int np, char *s, criterio_t crit);
void liberaCatalogo(prodotto_t *cat, int np);

int main()
{
  prodotto_t *catalogo;
  prodotto_t **rifOrd[cr_err];
  int np,maxp,fine=0,j;
  ComandoCompleto c;

  np = maxp = leggiCatalogo(&catalogo,rifOrd);
  if (np<=0) return 1;

  generaOrdini(catalogo, rifOrd, np);

  while(!fine) {
    c = leggiComando();
    switch(c.com) {
    case co_stampa:
      if (strcmp(c.altro,"stdout")!=0) {
	FILE *f = fopen(c.altro,"w");
	if (f!=NULL) {
	  stampaCatalogo(catalogo,rifOrd,np,f,c.crit);
	  fclose(f);
	}
      }
      else
	stampaCatalogo(catalogo,rifOrd,np,stdout,c.crit);
      break;
    case co_aggiorna:
      aggiorna(rifOrd,np,c.altro,c.crit);
      break;
    case co_cancella:
      cancella(rifOrd,np,c.altro,c.crit);
      break;
    case co_aggiungi:
      aggiungiProdotto(&catalogo, rifOrd, &np, &maxp, c.altro);
      break;
    case co_ricerca:
      ricercaStampa(rifOrd,np,c.altro,c.crit);
      break;
    case co_fine:
      fine = 1;
      break;
    default:
      break;
    }
  }
  for (j=0; crOrd[j]!=cr_err; j++)
    free(rifOrd[crOrd[j]]);
  liberaCatalogo(catalogo,np);
  free(catalogo);
  return 0;
}

int leggiCatalogo(prodotto_t **catP, prodotto_t **rOrd[])
{
  FILE *fp;
  int i,j,np;
  prodotto_t *cat;
  char nome[MAXS], categoria[MAXS];

  fp=fopen("catalogo.txt","r");
  if(fp==NULL) {
    fprintf(stderr,"Errore in apertura file");
    return 0;
  }
  fscanf(fp,"%d",&np);
  cat = (prodotto_t *)malloc(np*sizeof(prodotto_t));
  for (j=0; crOrd[j]!=cr_err; j++)
    rOrd[crOrd[j]] = (prodotto_t **)malloc(np*sizeof(prodotto_t *));

  for(i=0; i<np; i++) {
    fscanf(fp,"%s %s %s %f %d %d/%d/%d",cat[i].codice,nome,categoria,
	   &cat[i].prezzo,&cat[i].quant,
	   &cat[i].data.g,&cat[i].data.m,&cat[i].data.a);
    cat[i].nome = strdup(nome);
    cat[i].categoria = strdup(categoria);
    cat[i].cancellato = 0;
  }

  *catP=cat;
  fclose(fp);
  return np;
}

void generaOrdini(prodotto_t *cat, prodotto_t **rOrd[], int np)
{
  int i, j;

  for (j=0; crOrd[j]!=cr_err; j++) {
    criterio_t cr = crOrd[j];
    for(i=0; i<np; i++) {
      rOrd[cr][i] = &cat[i];
    }
    ordinaRifCatalogo (rOrd[cr], np, cr);
  }
  /* usa per nome parziale lo stesso ordine del nome completo */
  rOrd[cr_nomeParziale] = rOrd[cr_nome];
}

 void aggiungiProdotto(prodotto_t **catP, prodotto_t **rOrd[], int *npp, int *maxpp, char *s) {
  int i,j,k,np;
  prodotto_t *cat;
  char nome[MAXS], categoria[MAXS];

  cat = *catP;
  np = ++(*npp);
  if (np>*maxpp) {
    *maxpp *= 2;
    cat = (prodotto_t *)realloc(cat,(*maxpp)*sizeof(prodotto_t));
    for (j=0; crOrd[j]!=cr_err; j++)
      rOrd[crOrd[j]] = (prodotto_t **)realloc(rOrd[crOrd[j]],(*maxpp)*sizeof(prodotto_t *));
    /* riallinea vettori ordinati di puntatori */
    generaOrdini(cat, rOrd, np-1);
  }

  i = np-1;
  sscanf(s, "%s %s %s %f %d %d/%d/%d",cat[i].codice,nome,categoria,
	 &cat[i].prezzo,&cat[i].quant,
	 &cat[i].data.g,&cat[i].data.m,&cat[i].data.a);
  cat[i].nome = strdup(nome);
  cat[i].categoria = strdup(categoria);

  /* inserisci in ordine nei vettori di puntatori */
  for (j=0; crOrd[j]!=cr_err; j++) {
    criterio_t cr = crOrd[j];
    for(k=i-1; k>=0; k--) {
      if (confrontaProdotti(&cat[i],rOrd[cr][k],cr)<0) {
	rOrd[cr][k+1] = rOrd[cr][k];
      }
      else
	break;
    }
    rOrd[cr][k+1] = &cat[i];
  }

  *catP = cat;
}

void stampaProdotto(prodotto_t *p, FILE *fp) {
  if (!p->cancellato) {
    fprintf(fp, "%s %s %s %.2f %d %d/%d/%d\n",
	    p->codice, p->nome, p->categoria, p->prezzo, p->quant,
	    p->data.g, p->data.m, p->data.a);
  }
}

void stampaCatalogo(prodotto_t *cat, prodotto_t **rOrd[], int np, FILE *f, criterio_t crit) {
  int i, nc;
  for(i=nc=0;i<np;i++) {
    if (cat[i].cancellato) nc++;
  }
  fprintf(f,"%d\n",np-nc);
  for(i=0;i<np;i++) {
    if (crit==cr_tutto)
      stampaProdotto(&cat[i],f);
    else
      stampaProdotto(rOrd[crit][i],f);
  }
}

criterio_t leggiCriterio(criterio_t ammessi[]) {
  int i;
  char str[MAXS];

  printf("Criteri ammessi:\n");
  for (i=0; ammessi[i]!=cr_err; i++)
    printf(" %s", criteri[ammessi[i]]);
  printf("\nInserire un criterio: ");
  scanf("%s%*c",str);

  for (i=0; ammessi[i]!=cr_err; i++) {
    if (strcmp(str,criteri[ammessi[i]])==0)
      return ammessi[i];
  }
  return cr_err;
}

ComandoCompleto leggiComando() {
  char str[MAXS];
  comando_t c1;
  ComandoCompleto c;

  printf("Comandi validi:\n");
  for (c1=co_stampa; c1<co_err; c1++)
    printf(" %s", comandi[c1]);
  printf("\nInserire un comando: ");
  scanf("%s%*c",str);
  c1=co_stampa;
  while(c1<co_err && strcmp(str,comandi[c1])!=0)
    c1++;

  c.com = c1;

  switch (c1) {
  case co_stampa:
    {
      criterio_t ammessi[] = {cr_tutto,cr_categoria,cr_prezzoAsc,cr_prezzoDis, cr_codice,cr_nome,cr_err};
      c.crit = leggiCriterio(ammessi);
      printf("nome file (o stdout): ");
      scanf("%s%*c",c.altro);
    }
    break;
  case co_ricerca:
    {
      criterio_t ammessi[] = {cr_codice,cr_nome,cr_nomeParziale,cr_err};
      c.crit = leggiCriterio(ammessi);
      printf("nome da cercare: ");
      scanf("%s*c",c.altro);
    }
    break;
  case co_aggiorna:
    {
      criterio_t ammessi[] = {cr_codice,cr_nome,cr_err};
      c.crit = leggiCriterio(ammessi);
      printf("nome da aggiornare e quantita': ");
      fgets(c.altro,sizeof(c.altro)/sizeof(char),stdin);
    }
    break;
  case co_aggiungi:
    {
      printf("dati del nuovo prodotto (una riga): ");
      fgets(c.altro,sizeof(c.altro)/sizeof(char),stdin);
    }
    break;
  case co_cancella:
    {
      criterio_t ammessi[] = {cr_codice,cr_nome,cr_err};
      c.crit = leggiCriterio(ammessi);
      printf("nome/codice da cancellare': ");
      scanf("%s*c",c.altro);
    }
    break;
  case co_err:
  case co_fine:
  default:
    break;
  }

  return c;
}

int confrontaProdotti (prodotto_t *a, prodotto_t *b, criterio_t crit) {
  switch (crit) {
  case cr_categoria:
    return strcmp(a->categoria,b->categoria);
    break;
  case cr_prezzoAsc:
    return a->prezzo-b->prezzo;
    break;
  case cr_prezzoDis:
    return b->prezzo-a->prezzo;
    break;
  case cr_codice:
    return strcmp(a->codice,b->codice);
    break;
  case cr_nome:
    return strcmp(a->nome,b->nome);
    break;
  case cr_nomeParziale:
    { int l = strlen(b->nome);
      return strncmp(a->nome,b->nome,l);
    }
    break;
  default: fprintf(stderr,"codice errato in confronto prodotti");
    return 0; /* risultato arbitrario */
  }
}

void ordinaRifCatalogo (prodotto_t **catR, int np, criterio_t crit) {
  int i,j;
  prodotto_t *temp;

  for(i=1;i<np;i++) {
    temp=catR[i];
    j=i-1;
    while(j>=0 && confrontaProdotti(temp,catR[j],crit)<0) {
      catR[j+1]=catR[j];
      j--;
    }
    catR[j+1]=temp;
  }
}

int ricercaDicotomica(prodotto_t **catR, int np, prodotto_t *p, criterio_t crit) {
  int l=0, r=np-1;
  int m;
  while(l<=r) {
    m=l+(r-l)/2;
    if (confrontaProdotti(catR[m],p,crit)==0) {
      return m;
    }
    else if (confrontaProdotti(catR[m],p,crit)<0)
      l=m+1;
    else r=m-1;
  }
  return -1;
}

void ricercaStampa(prodotto_t **rOrd[], int np, char *s, criterio_t crit) {
  int i, i0, i1;
  prodotto_t tmp;
  prodotto_t **catR = rOrd[crit];
  if (crit==cr_codice)
    strcpy(tmp.codice,s);
  else tmp.nome=s;

  i = ricercaDicotomica(catR,np,&tmp,crit);
  if (i<0) {
    printf("prodotto non trovato\n");
    return;
  }

  for (i0=i-1; i0>=0 && confrontaProdotti(catR[i0],&tmp,crit)==0; i0--);
  for (i1=i+1; i1<np && confrontaProdotti(catR[i1],&tmp,crit)==0; i1++);

  for (i=i0+1; i<i1; i++) {
    stampaProdotto(catR[i],stdout);
  }

}

void cancella(prodotto_t **rOrd[], int np, char *s, criterio_t crit) {
  int i;
  prodotto_t tmp;
  prodotto_t **catR = rOrd[crit];
  if (crit==cr_codice)
    strcpy(tmp.codice,s);
  else tmp.nome=s;

  i = ricercaDicotomica(catR,np,&tmp,crit);
  if (i<0) {
    printf("prodotto non trovato\n");
  }
  else
    catR[i]->cancellato = 1;
}

void aggiorna(prodotto_t **rOrd[], int np, char *s, criterio_t crit) {
  int i, q;
  char nome_o_codice[MAXS];
  prodotto_t tmp;
  prodotto_t **catR = rOrd[crit];

  sscanf(s,"%s%d", nome_o_codice, &q);
  if (crit==cr_codice)
    strcpy(tmp.codice,nome_o_codice);
  else tmp.nome=nome_o_codice;

  i = ricercaDicotomica(catR,np,&tmp,crit);

  if (i<0) {
    printf("prodotto non trovato\n");
    return;
  }
  catR[i]->quant = q;
  printf("Prodotto con quantita' aggiornata:\n");
  stampaProdotto(catR[i],stdout);
}


void liberaCatalogo(prodotto_t *cat, int np) {
  int i;
  for(i=0; i<np; i++) {
    free(cat[i].nome);
    free(cat[i].categoria);
  }
}
