#include "grafo.h"
#include <limits.h>

struct grafo{
   int V, E, nRegali;
   ST table;
   int **matAdj;
};



static int **MATRIXinit(int nr, int nc, int value){
    int **mat, i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
           mat[i][j]=-1;
    return mat;
}

Grafo GRAFOinit(){
   Grafo g;
   g=(Grafo)malloc(sizeof(struct grafo));
   if(g==NULL) exit(EXIT_FAILURE);
   g->V=0;
   g->E=0;
   g->table=STinit(1);
   g->nRegali=0;
   g->matAdj=NULL;
   return g;
}


Grafo GRAFOload(FILE *f){
   Grafo g=GRAFOinit();
   int id1, id2;
   char label1[MAX], label2[MAX];
   Amico a;
   a=AMICOread(f);
   while(AMICOisNull(a)==FALSO){
      id1=STsearch(g->table, a.nome);
      if(id1==-1){
         (g->V)++;
         STinsert(g->table, a);
      }
      a=AMICOread(f);
   }
   g->matAdj=MATRIXinit(g->V, g->V, -1);
   rewind(f);
   while(fscanf(f, "%s %s", label1, label2)==2){
      id1=STsearch(g->table, label1);
      id2=STsearch(g->table, label2);
      if(id1!=-1 && id2!=-1)
         GRAFOinsertE(g, id1, id2);
   }
   return g;
}


void GRAFOinsertE(Grafo g, int id1, int id2){
    if(g->matAdj[id1][id2]==-1){
        g->matAdj[id1][id2]=1;
        g->matAdj[id2][id1]=1;
        (g->E)++;
    }
    return;
}


Boolean GRAFOleggiProposta(Grafo g, FILE *f){
    int regalo, amico, amicoPrec=-1, i, nAmiciRegalo;
    char label[MAX];
    Amico *a;
    fscanf(f, "%d", &g->nRegali);
    for(regalo=1; regalo<=g->nRegali; regalo++){
       fscanf(f, "%d", &nAmiciRegalo);
       for(i=0; i<nAmiciRegalo; i++){
          fscanf(f, "%s", label);
          amico=STsearch(g->table, label);
          if(amico!=-1){
             if(amicoPrec!=-1 && g->matAdj[amico][amicoPrec]!=-1)
                return FALSO;
             a=STgetAmicoByIndex(g->table, amico);
             if(a->regalo!=EMPTY)
                return FALSO;
             a->regalo=regalo;
          }
       }
    }
    for(amico=0; amico<g->V; amico++){
       a=STgetAmicoByIndex(g->table, amico);
       if(a->regalo==EMPTY)
          return FALSO;
    }
    return VERO;
}


Boolean GRAFOverifica(Grafo g, char *nomeFile){
   FILE *f=fopen(nomeFile, "r");
   if(f==NULL) exit(EXIT_FAILURE);
   return GRAFOleggiProposta(g, f);
}


void GRAFOeliminaRegali(Grafo g){
   int i;
   Amico *a;
   for(i=0; i<g->V; i++){
      a=STgetAmicoByIndex(g->table, i);
      a->regalo=EMPTY;
   }
   return;
}


static Boolean checkRegaliTraAmici(Grafo g, int *amici, int amico, int regalo){
   int i;
   for(i=0; i<g->V; i++){
      if(amici[i]==regalo && g->matAdj[amico][i]!=-1){
         return FALSO;
      }
   }
   return VERO;
}

static int calcolaNumeroRegali(int *amici, int dim){
   int *regali, i, count=0;
   regali=calloc(dim, sizeof(int));
   if(regali==NULL) exit(EXIT_FAILURE);

   for(i=0; i<dim; i++)
      if(amici[i]!=0)
         regali[amici[i]-1]=1;

   for(i=0; i<dim; i++)
      if(regali[i]==1)
         count++;
   return count;
}

static void dispRip(Grafo g, int *amici, int *bestSol, int *min, int pos){
   int regalo, nRegali, i;

   nRegali=calcolaNumeroRegali(amici, g->V);

   if(nRegali>(*min)){
      return;
   }

   if(pos>=g->V){
      if(nRegali<(*min)){
         (*min)=nRegali;
         for(i=0; i<g->V; i++)
            bestSol[i]=amici[i];
      }
      return;
   }
   for(regalo=1; regalo<=g->V; regalo++){
      if(checkRegaliTraAmici(g, amici, pos, regalo)==FALSO)
         continue;
      amici[pos]=regalo;
      dispRip(g, amici, bestSol, min, pos+1);
   }
   return;
}

void GRAFOsolve(Grafo g){
   int *amici, min=INT_MAX, *bestSol, regalo, amico;
   Amico *a;

   amici=calloc(g->V, sizeof(int));
   if(amici==NULL) exit(EXIT_FAILURE);

   bestSol=(int*)malloc(g->V*sizeof(int));
   if(bestSol==NULL) exit(EXIT_FAILURE);

   dispRip(g, amici, bestSol, &min, 0);

   printf("Best Solution:\n");
   printf("Numero Regali: %d\n", min);
   for(regalo=1; regalo<=min; regalo++){
      printf("Regalo %d = { ", regalo);
      for(amico=0; amico<g->V; amico++){
         if(bestSol[amico]==regalo){
            a=STgetAmicoByIndex(g->table, amico);
            printf("%s ", a->nome);
         }
      }
      printf("}\n");
   }

   free(amici);
   free(bestSol);
   return;
}


static void free2D(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++)
            free(mat[i]);
        free(mat);
    }
    return;
}

void GRAFOfree(Grafo g){
    if(g!=NULL){
        free2D(g->matAdj, g->V);
        STfree(g->table);
        free(g);
    }
}
