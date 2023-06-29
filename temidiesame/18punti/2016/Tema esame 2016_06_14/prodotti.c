#include "prodotti.h"

struct prods{
   Prodotto *prodotti;
   int maxD, size;
};



static int ricercaDicotomicaR(Prodotto *vett, int left, int right, char *code){
    int mezzo;
    if(left>right)
        return -1;
    mezzo=(left+right)/2;
    if(strcmp(vett[mezzo].id, code)==0)
        return mezzo;
    if(strcmp(code, vett[mezzo].id)>0)
       return ricercaDicotomicaR(vett, mezzo+1, right, code);
    return ricercaDicotomicaR(vett, left, mezzo-1, code);
}

static int ricercaDicotomica(Prodotto *vett, int dim, char *code){
    return ricercaDicotomicaR(vett, 0, dim-1, code);
}


static int resultOrdinamento(Prodotto p1, Prodotto p2, char *ordinamento){
    if(strcmp(ordinamento, "nome")==0)
        return strcmp(p1.nome, p2.nome);
    return strcmp(p1.id, p2.id);
}

static void merge(Prodotto *p, Prodotto *B, int left, int mezzo, int right, char *ordinamento){
    int i, j, k;
    i=left;
    j=mezzo+1;
    for(k=left; k<=right; k++){
        if(i>mezzo)
            B[k]=p[j++];
        else if(j>right)
            B[k]=p[i++];
        else if(resultOrdinamento(p[i], p[j], ordinamento)<0)
            B[k]=p[i++];
        else
            B[k]=p[j++];
    }
    for(k=left; k<=right; k++){
        p[k]=B[k];
    }
    return;
}

static void mergeSortR(Prodotto *vett, Prodotto *B, int left, int right, char *ordinamento){
    int mezzo;
    if(left>=right)
        return;
    mezzo=(left+right)/2;
    mergeSortR(vett, B, left, mezzo, ordinamento);
    mergeSortR(vett, B, mezzo+1, right, ordinamento);
    merge(vett, B, left, mezzo, right, ordinamento);
    return;
}

static void mergeSort(Prodotto *p, int dim, char *ordinamento){
    Prodotto *B;
    B=(Prodotto*)malloc(dim*sizeof(Prodotto));
    if(B==NULL) exit(EXIT_FAILURE);
    mergeSortR(p, B, 0, dim-1, ordinamento);
    return;
}


Prodotti PRODOTTIinit(){
   Prodotti p;
   p=(Prodotti)malloc(sizeof(struct prods));
   if(p==NULL) exit(EXIT_FAILURE);
   p->maxD=1;
   p->size=0;
   p->prodotti=(Prodotto*)malloc(p->maxD*sizeof(Prodotto));
   if(p->prodotti==NULL) exit(EXIT_FAILURE);
   return p;
}


//inserimento ordinato per codice
void PRODOTTIinsert(Prodotti ps, Prodotto p){
   int i;
   if(ps->size==ps->maxD){
      ps->maxD=2*ps->maxD;
      ps->prodotti=realloc(ps->prodotti, ps->maxD*sizeof(Prodotto));
      if(ps->prodotti==NULL) exit(EXIT_FAILURE);
   }
   i=ps->size-1;
   while(strcmp(p.id, ps->prodotti[i].id)<0){
      ps->prodotti[i+1]=ps->prodotti[i];
      i--;
   }
   ps->prodotti[i+1]=p;
   (ps->size)++;
   return;
}


Prodotto *PRODOTTIsearch(Prodotti p, char *code){
   int id;
   id=ricercaDicotomica(p->prodotti, p->size, code);
   if(id==-1)
      return NULL;
   return &p->prodotti[id];
}


Prodotti PRODOTTIsearchByName (Prodotti pr, char *name){
   int i;
   Prodotti ricerca=PRODOTTIinit();
   if(strstr(name, "*")!=NULL){
      name[strlen(name)-1]='\0';
      for(i=0; i<pr->size; i++){
         if(strstr(pr->prodotti[i].nome, name)!=NULL)
            PRODOTTIinsert(ricerca, pr->prodotti[i]);
      }
   }
   else{
      for(i=0; i<pr->size; i++){
         if(strcmp(pr->prodotti[i].nome, name)==0)
            PRODOTTIinsert(ricerca, pr->prodotti[i]);
      }
   }
   return ricerca;
}


void PRODOTTIordinaPerNome(Prodotti p){
   mergeSort(p->prodotti, p->size, "nome");
   return;
}


void PRODOTTIordinaPerCodice(Prodotti p){
   mergeSort(p->prodotti, p->size, "codice");
   return;
}


void PRODOTTIprint(Prodotti p, FILE *f){
   int i;
   for(i=0; i<p->size; i++)
      PRODOTTOprint(p->prodotti[i], f);
   return;
}


int PRODOTTIgetSize(Prodotti p){
    return p->size;
}


void PRODOTTIfree(Prodotti p){
   if(p!=NULL){
      if(p->prodotti!=NULL)
         free(p->prodotti);
      free(p);
   }
   return;
}
