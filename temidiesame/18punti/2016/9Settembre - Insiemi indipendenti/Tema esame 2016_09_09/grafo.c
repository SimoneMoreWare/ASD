#include "grafo.h"

struct grafo{
   int V, E;
   int **matAdj;
   ST table;
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
           mat[i][j]=value;
    return mat;
}

Grafo GRAFOinit(){
   Grafo g;
   g=(Grafo)malloc(sizeof(struct grafo));
   if(g==NULL) exit(EXIT_FAILURE);
   g->V=0;
   g->E=0;
   g->matAdj=NULL;
   g->table=STinit(1);
   return g;
}


Grafo GRAFOload(FILE *f){
   Grafo g=GRAFOinit();
   Vertice v;
   char label1[MAX], label2[MAX];
   int id1, id2;
   v=VERTICEread(f);
   while(VERTICEisNull(v)==FALSO){
      id1=STsearch(g->table, v.identificatore);
      if(id1==-1){
         STinsert(g->table, v);
         (g->V)++;
      }
      v=VERTICEread(f);
   }
   rewind(f);
   g->matAdj=MATRIXinit(g->V, g->V, -1);
   while(fscanf(f, "%s %s", label1, label2)==2){
      id1=STsearch(g->table, label1);
      id2=STsearch(g->table, label2);
      if(id1!=-1 && id2!=-1){
         GRAFOinsertE(g, id1, id2);
      }
   }
   return g;
}


void GRAFOinsertE(Grafo g, int id1, int id2){
    if(g->matAdj[id1][id2]==-1){
        g->matAdj[id2][id1]=1;
        g->matAdj[id1][id2]=1;
        (g->E)++;
    }
    return;
}


static int *readProposta(Grafo g, FILE *f, int *dim){
   int id, size=0, maxD=1, *vertici;
   char label[MAX];
   vertici=(int*)malloc(maxD*sizeof(int));
   if(vertici==NULL) exit(EXIT_FAILURE);
   while(fscanf(f, "%s", label)==1){
      id=STsearch(g->table, label);
      if(id==-1)
         return NULL;
      if(maxD==size){
         maxD=2*maxD;
         vertici=realloc(vertici, maxD*sizeof(int));
         if(vertici==NULL) exit(EXIT_FAILURE);
      }
      vertici[size++]=id;
   }
   (*dim)=size;
   return vertici;
}

static Boolean isInsiemeIndipendente(Grafo g, int *vertici, int dim){
   int i, j, v, w;
   for(i=0; i<dim-1; i++){
      v=vertici[i];
      for(j=i+1; j<dim; j++){
         w=vertici[j];
         if(g->matAdj[v][w]!=-1)
            return FALSO;
      }
   }
   return VERO;
}

Boolean GRAFOverifica(Grafo g, char *nomeFile){
   FILE *f;
   int *proposta, dim;
   f=fopen(nomeFile, "r");
   if(f==NULL) exit(EXIT_FAILURE);
   proposta=readProposta(g, f, &dim);
   if(proposta==NULL)
      return FALSO;
   return isInsiemeIndipendente(g, proposta, dim);
}


static void solveR(Grafo g, int *sol, int *bestSol, int *bestCard, int pos, int start){
   int i, j;
   if(pos>1 && pos>(*bestCard) && isInsiemeIndipendente(g, sol, pos)==VERO){
      (*bestCard)=pos;
      for(j=0; j<pos; j++)
         bestSol[j]=sol[j];
   }
   if(pos>=g->V)
      return;
   for(i=start; i<g->V; i++){
      sol[pos]=i;
      solveR(g, sol, bestSol, bestCard, pos+1, i+1);
   }
   return;
}

void GRAFOsolve(Grafo g){
   int *sol, *bestSol, max=0, i;
   Vertice v;
   sol=(int*)malloc(g->V*sizeof(int));
   bestSol=(int*)malloc(g->V*sizeof(int));
   if(sol==NULL || bestSol==NULL) exit(EXIT_FAILURE);
   solveR(g, sol, bestSol, &max, 0, 0);
   printf("Best Solution (Insieme Indipendente Massimale):\n");
   printf("   - Cardinalita': %d\n", max);
   printf("   - Vertici: {");
   for(i=0; i<max; i++){
      v=STsearchByIndex(g->table, bestSol[i]);
      VERTICEprint(v, stdout);
      printf("%s", (i==max-1)?"}":", ");
   }
   printf("\n");
   return;
}


static void MATRIXfree(int **mat, int nr){
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
        MATRIXfree(g->matAdj, g->V);
        STfree(g->table);
        free(g);
    }
    return;
}
