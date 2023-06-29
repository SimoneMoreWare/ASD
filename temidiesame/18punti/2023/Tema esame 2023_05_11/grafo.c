#include "grafo.h"

struct grafo{
   int V, E;
   int **matAdj;
};


static int **MATRIXinit(int nr, int nc, int value){
    int i, j;
    int **mat;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            mat[i][j]=value;
        }
    }
    return mat;
}

Grafo GRAFOinit(int V){
    Grafo g;
    g=(Grafo)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);
    g->V=V;
    g->E=0;
    g->matAdj=MATRIXinit(g->V, g->V, -1);
    return g;
}


Grafo GRAFOload(FILE *f){
   Grafo g;
   int V, id1, id2;

   fscanf(f, "%d", &V);
   g=GRAFOinit(V);

   while(fscanf(f, "%d %d", &id1, &id2)==2){
      if(id1>=0 && id1<V && id2>=0 && id2<V)
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


Boolean GRAFOverifica(Grafo g, char *nomeFile){
   FILE *f;
   TP proposta;

   f=fopen(nomeFile, "r");
   if(f==NULL) exit(EXIT_FAILURE);

   proposta=TPread(f);

   return TPisTrianglePacking(proposta, g->matAdj, g->V);
}


static void combSemp(Grafo g, V *val, int *dim, int *maxD, int *sol, int dimInsieme, int pos, int start){
   int i;
   V v;
   if(pos>=dimInsieme){
      v=Vcreate(sol);
      if(VareThereRealEdges(v, g->matAdj)==VERO){
         if((*dim)==(*maxD)){
            (*maxD)=2*(*maxD);
            val=realloc(val, (*maxD)*sizeof(V));
            if (val==NULL) exit(EXIT_FAILURE);
         }
         val[(*dim)]=v;
         (*dim)++;
       }
       return;
   }
   for(i=start; i<g->V; i++){
      sol[pos]=i;
      combSemp(g, val, dim, maxD, sol, dimInsieme, pos+1, i+1);
   }
   return;
}

void findTP(V *val, int dim, TP solFin, TP bestSol, int pos, int start, Boolean *trovato, int *max){
    int i;
    if(pos>1 && TPisDisgiunto(solFin)==FALSO){
       return;
    }
    if(pos>(*max)){
       (*max)=pos;
       TPcopia(solFin, bestSol);
       *trovato=VERO;
    }
    if(pos>=dim){
       *trovato=VERO;
       return;
    }
    for(i=start; i<dim; i++){
       TPinsert(solFin, val[i]);
       findTP(val, dim, solFin, bestSol, pos+1, i+1, trovato, max);
       TPelimina(solFin);
    }
    return;
}

void GRAFOsolve(Grafo g){
   V *val;
   int dim=0, maxD=1, max=0;
   int sol[3];
   TP solFin, bestSol;
   Boolean trovato=FALSO;

   val=(V*)malloc(maxD*sizeof(V));
   if (val==NULL) exit(EXIT_FAILURE);

   combSemp(g, val, &dim, &maxD, sol, 3, 0, 0);

   solFin=TPinit(dim);

   bestSol=TPinit(dim);

   findTP(val, dim, solFin, bestSol, 0, 0, &trovato, &max);
   if(trovato==FALSO){
      printf("Soluzione non trovata.\n");
      return;
   }
   printf("Best Solution:\n");
   TPprint(bestSol, stdout);
   printf("\n");
   return;
}


static void free2d(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL)
                free(mat[i]);
        }
        free(mat);
    }
    return;
}

void GRAFOfree(Grafo g){
    if(g!=NULL){
        free2d(g->matAdj, g->V);
        free(g);
    }
}
