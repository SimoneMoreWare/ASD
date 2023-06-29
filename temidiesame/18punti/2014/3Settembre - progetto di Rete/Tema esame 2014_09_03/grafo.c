#include "grafo.h"
#include <limits.h>

struct grafo{
   int E, V;
   ST table;
   int **matAdj;
};



int **MATRIXinit(int nr, int nc, int value){
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
   g->E=0;
   g->V=0;
   g->table=STinit(1);
   g->matAdj=NULL;
   return g;
}


Grafo GRAFOload(FILE *f){
   Grafo g=GRAFOinit();
   Vertice v;
   int id;
   v=VERTICEread(f);
   while(VERTICEisNull(v)==FALSO){
      (g->V)++;
	id=STsearch(g->table, v.nome);
      if(id==-1)
         STinsert(g->table, v);
      v=VERTICEread(f);
   }
   g->matAdj=MATRIXinit(g->V, g->V, -1);
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


void GRAFOdeleteE(Grafo g, int id1, int id2){
    g->matAdj[id1][id2]=-1;
    g->matAdj[id2][id1]=-1;
    (g->E)--;
    return;
}


static void azzeraVettore(int *vett, int dim){
   int i;
   for(i=0; i<dim; i++)
      vett[i]=0;
   return;
}

static Boolean path(Grafo g, int v, int end, int *visited){
   int w;
   if(v==end){
      return VERO;
   }
   for(w=0; w<g->V; w++){
   	if(g->matAdj[v][w]!=-1 && visited[w]==0){
         visited[w]=1;
         if(path(g, w, end, visited)==VERO)
           return VERO;
         visited[w]=0;
      }
   }
   return FALSO;
}

Boolean GRAFOisConnesso(Grafo g){
   int start, end;
   int *visited;

   visited=(int*)malloc(g->V*sizeof(int));
   if(visited==NULL) exit(EXIT_FAILURE);

   for(start=0; start<g->V; start++){
      for(end=start+1; end<g->V; end++){
        azzeraVettore(visited, g->V);
        if(path(g, start, end, visited)==FALSO)
            return FALSO;
      }
   }
   return VERO;
}


Boolean GRAFOcheckGrado(Grafo g, int m){
    int v;
    Vertice *ver;
    for(v=0; v<g->V; v++){
       ver=STgetVerticeByIndex(g->table, v);
       if(ver->grado > m)
          return FALSO;
    }
    return VERO;
}


void GRAFOleggiArchi(Grafo g, FILE *f){
    char label1[MAX], label2[MAX];
    int id1, id2;
    Vertice *v1, *v2;

    while(fscanf(f, "%s %s", label1, label2)==2){
       id1=STsearch(g->table, label1);
       id2=STsearch(g->table, label2);
       if(id1!=-1 && id2!=-1){
          GRAFOinsertE(g, id1, id2);
          v1=STgetVerticeByIndex(g->table, id1);
          v2=STgetVerticeByIndex(g->table, id2);
          VERTICEincrementaGrado(v1);
          VERTICEincrementaGrado(v2);
       }
   }
   return;
}


Boolean GRAFOverifica(Grafo g, int k, int m){
   FILE *f;
   f=fopen("proposta.txt", "r");
   if(f==NULL) exit(EXIT_FAILURE);
   GRAFOleggiArchi(g, f);
   if(GRAFOcheckGrado(g, m)==VERO && GRAFOcheckCamminiMinimi(g, k)==VERO)
     return VERO;
   return FALSO;
}


static void combSemp(Grafo g, Archi a, int *sol, int dimInsieme, int pos, int start){
   Edge e;
   int i;
   if(pos>=dimInsieme){
      e=EDGEcreate(sol[0], sol[1]);
      ARCHIinsert(a, e);
      return;
   }
   for(i=start; i<g->V; i++){
      sol[pos]=i;
      combSemp(g, a, sol, dimInsieme, pos+1, i+1);
   }
   return;
}

Archi GRAFOgeneraArchi(Grafo g){
   Archi a=ARCHIinit();
   int sol[2];

   combSemp(g, a, sol, 2, 0, 0);
   return a;
}


static void combsemp(Grafo g, Edge *val, int dim, int m, int k, Edge *sol, Edge *bestSol, int *min, int pos, int start){
    int i, j;
    Vertice *v1, *v2;
    if(pos > (*min)){
       return;
    }
    if(pos>=dim){
       return;
    }
    if(pos>0 && pos < (*min)){
       for(i=0; i<pos; i++){
          GRAFOinsertE(g, sol[i].v, sol[i].w);
          v1=STgetVerticeByIndex(g->table, sol[i].v);
          v2=STgetVerticeByIndex(g->table, sol[i].w);
          VERTICEincrementaGrado(v1);
          VERTICEincrementaGrado(v2);
       }
       if(GRAFOcheckGrado(g, m)==VERO && GRAFOisConnesso(g)==VERO && GRAFOcheckCamminiMinimi(g, k)==VERO){
          (*min)=pos;
          for(i=0; i<pos; i++){
             bestSol[i]=sol[i];
          }
       }
       for(i=0; i<pos; i++){
          GRAFOdeleteE(g, sol[i].v, sol[i].w);
          v1=STgetVerticeByIndex(g->table, sol[i].v);
          v2=STgetVerticeByIndex(g->table, sol[i].w);
          VERTICEdecrementaGrado(v1);
          VERTICEdecrementaGrado(v2);
       }
    }
    for(j=start; j<dim; j++){
       sol[pos]=val[j];
       combsemp(g, val, dim, m, k, sol, bestSol, min, pos+1, j+1);
    }
    return;
}

void GRAFOsolve(Grafo g, int m, int k){
   Archi a=GRAFOgeneraArchi(g);
   int min=INT_MAX, i;
   int dim=ARCHIsize(a);
   Edge *sol, *bestSol;
   Vertice *v1, *v2;

   sol=(Edge*)malloc(dim*sizeof(Edge));
   if(sol==NULL) exit(EXIT_FAILURE);

   bestSol=(Edge*)malloc(dim*sizeof(Edge));
   if(bestSol==NULL) exit(EXIT_FAILURE);

   combsemp(g, ARCHIgetArchi(a), dim, m, k, sol, bestSol, &min, 0, 0);

   printf("Best Solution: \n");
   printf("Cardinalita: %d\n", min);
   printf("Archi:\n");
   for(i=0; i<min; i++){
        v1=STgetVerticeByIndex(g->table, bestSol[i].v);
        v2=STgetVerticeByIndex(g->table, bestSol[i].w);
        printf("%s %s\n", v1->nome, v2->nome);
   }
   free(sol);
   free(bestSol);
   ARCHIfree(a);
   return;
}


static Boolean bfs(Grafo g, int id, int k){
   Q q=Qinit();
   int vertice, v, *lunghezze, *visited;

   lunghezze=calloc(g->V, sizeof(int));
   if(lunghezze==NULL) exit(EXIT_FAILURE);

   visited=calloc(g->V, sizeof(int));
   if(visited==NULL) exit(EXIT_FAILURE);

   Qput(q, id);

   while(!Qempty(q)){
      vertice=Qget(q);
      for(v=0; v<g->V; v++){
         if(g->matAdj[vertice][v]!=-1 && visited[v]==0){
            if(lunghezze[vertice]+1>k)
               return FALSO;
            lunghezze[v]=lunghezze[vertice]+1;
            visited[v]=1;
            Qput(q, v);
         }
      }
   }
   Qfree(q);
   return VERO;
}

Boolean GRAFOcheckCamminiMinimi(Grafo g, int k){
   int v;
   for(v=0; v<g->V; v++){
      if(bfs(g, v, k)==FALSO)
         return FALSO;
   }
   return VERO;
}


void GRAFOdeleteArchi(Grafo g){
    int i, j;
    Vertice *v;
    for(i=0; i<g->V; i++)
        for(j=0; j<g->V; j++)
            g->matAdj[i][j]=-1;
    for(i=0; i<g->V; i++){
        v=STgetVerticeByIndex(g->table, i);
        VERTICEazzeraGrado(v);
    }
    return;
}


void MATRIXfree(int **mat, int nr){
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
        STfree(g->table);
        MATRIXfree(g->matAdj, g->V);
        free(g);
    }
}
