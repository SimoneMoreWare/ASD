#include "grafo.h"
#include <math.h>

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
   g->table=STinit(1);
   g->matAdj=NULL;
   return g;
}


Grafo GRAFOload(FILE *f){
   Vertice v, v1;
   int id, id1, wt;
   char label[MAX], label1[MAX], colore[6], colore1[6];
   Grafo g=GRAFOinit();
   v=VERTICEread(f);
   while(VERTICEisNull(v)==FALSO){
      id=STsearch(g->table, v.identificatore);
      if(id==-1){
         (g->V)++;
         STinsert(g->table, v);
      }
      fscanf(f, "%*d");
      v=VERTICEread(f);
   }
   g->matAdj=MATRIXinit(g->V, g->V, -1);
   rewind(f);
   while(fscanf(f,"%s %s %d %s %s", label, colore, &wt, label1, colore1)==5){
      id=STsearch(g->table, label);
      id1=STsearch(g->table, label1);
      if(id!=-1 && id1!=-1){
         v=STgetVerticeByIndex(g->table, id);
         v1=STgetVerticeByIndex(g->table, id1);
         if((v.colore==ROSSO && strcmp(colore, "ROSSO")!=0) || (v.colore==NERO && strcmp(colore, "NERO")!=0))
            return NULL;
         if((v1.colore==ROSSO && strcmp(colore1, "ROSSO")!=0) || (v1.colore==NERO && strcmp(colore1, "NERO")!=0))
            return NULL;
         GRAFOinsertE(g, id, id1, wt);
      }
   }
   return g;
}


void GRAFOinsertE(Grafo g, int id1, int id2, int wt){
    if(g->matAdj[id1][id2]==-1){
        g->matAdj[id2][id1]=wt;
        g->matAdj[id1][id2]=wt;
        (g->E)++;
    }
    return;
}


static void pathMax(Grafo g, int v, int*sol, int *bestSol, int *bestLun, int *max, int *visited, int pos, int peso){
   Boolean fine=VERO;
   int w, i;
   Vertice v1, v2;

   v1=STgetVerticeByIndex(g->table, v);
   for(w=0; w<g->V; w++){
       if(visited[w]==0 && g->matAdj[v][w]!=-1){
          v2=STgetVerticeByIndex(g->table, w);
          if((v1.colore==NERO && (v2.colore==ROSSO || v2.colore==NERO)) || (v1.colore==ROSSO && v2.colore==NERO)){
             visited[w]=1;
             sol[pos]=w;
             peso+=g->matAdj[v][w];
             pathMax(g, w, sol, bestSol, bestLun, max, visited, pos+1, peso);
             peso-=g->matAdj[v][w];
             visited[w]=0;
             fine=FALSO;
          }
       }
   }

   if(fine==VERO){
      if(peso>(*max)){
         (*max)=peso;
         (*bestLun)=pos;
         for(i=0; i<pos; i++)
            bestSol[i]=sol[i];
      }
   }
   return;
}

void GRAFOcamminoPesoMax(Grafo g){
   int *sol, *bestSol, *visited=0, max=0, i, bestLun;
   Vertice v;
   sol=(int*)malloc(g->V*sizeof(int));
   bestSol=(int*)malloc(g->V*sizeof(int));
   if(sol==NULL || bestSol==NULL)
      exit(EXIT_FAILURE);

   for(i=0; i<g->V; i++){
      visited=(int*)calloc(g->V, sizeof(int));
      if(visited==NULL) exit(EXIT_FAILURE);
      sol[0]=i;
      visited[i]=1;
      pathMax(g, i, sol, bestSol, &bestLun, &max, visited, 1, 0);
      free(visited);
   }
   printf("BestSolution:\n");
   printf("Peso: %d\n", max);
   printf("Vertici: ");
   for(i=0; i<bestLun; i++){
      v=STgetVerticeByIndex(g->table, bestSol[i]);
      printf("%s %s%s", v.identificatore, (v.colore==ROSSO)?"ROSSO":"NERO",(i==bestLun-1)?"":", ");
   }
   return;
}


static void dfs(Grafo g, int v, int *vertici, int dim, int *visited){
   int i, w;
   for(i=0; i<dim; i++){
      w=vertici[i];
      if(g->matAdj[v][w]!=-1 && visited[i]==0){
         visited[i]=1;
         dfs(g, w, vertici, dim, visited);
      }
   }
   return;
}

static Boolean isConnesso(Grafo g, int *vertici, int dim){
   int *visited, start, i;
   visited=calloc(dim, sizeof(int));
   if(visited==NULL) exit(EXIT_FAILURE);
   start=vertici[0];
   dfs(g, start, vertici, dim, visited);
   for(i=0; i<dim; i++){
       if(visited[i]==0)
          return FALSO;
   }
   return VERO;
}

static int checkDifferenza(Grafo g, int *vertici, int dim){
   int i, nRossi=0, nNeri=0;
   Vertice v;
   for(i=0; i<dim; i++){
      v=STgetVerticeByIndex(g->table, vertici[i]);
      if(v.colore==ROSSO)
         nRossi++;
      else if(v.colore==NERO)
         nNeri++;
   }
   return abs(nRossi-nNeri);
}

static int getPeso(Grafo g, int *vertici, int dim){
   int peso=0;
   int i, j, v, w;
   for(i=0; i<dim-1; i++){
      v=vertici[i];
      for(j=i+1; j<dim; j++){
         w=vertici[j];
         if(g->matAdj[v][w]!=-1)
            peso+=g->matAdj[v][w];
      }
   }
   return peso;
}

static void sottoGrafoR(Grafo g, int *sol, int *bestSol, int *bestLun, int* max, int pos, int start){
    int i, j, peso;
    if(pos>0 && isConnesso(g, sol, pos)==VERO){
       peso=getPeso(g, sol, pos);
       if(peso>(*max) && checkDifferenza(g, sol, pos)<=2){
          (*max)=peso;
          (*bestLun)=pos;
          for(j=0; j<pos; j++){
             bestSol[j]=sol[j];
          }
       }
    }
    if(pos>=g->V){
       return;
    }
    for(i=start; i<g->V; i++){
       sol[pos]=i;
       sottoGrafoR(g, sol, bestSol, bestLun, max, pos+1, i+1);
    }
    return;
}

void GRAFOsottoGrafo(Grafo g){
   int *sol, *bestSol, max=0, bestLun, i;
   Vertice v;
   sol=(int *)malloc(g->V*sizeof(int));
   bestSol=(int*)malloc(g->V*sizeof(int));
   if(sol==NULL || bestSol==NULL) exit(EXIT_FAILURE);
   sottoGrafoR(g, sol, bestSol, &bestLun, &max, 0, 0);
   printf("Best Solution:\n");
   printf("Peso: %d\n", max);
   printf("Vertici: ");
   for(i=0; i<bestLun; i++){
      v=STgetVerticeByIndex(g->table, bestSol[i]);
      printf("%s %s%s", v.identificatore, (v.colore==ROSSO)?"ROSSO":"NERO",(i==bestLun-1)?"":", ");
   }
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
