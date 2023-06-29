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
   g->table=STinit(1);
   g->matAdj=NULL;
   return g;
}

Grafo GRAFOload(FILE *f){
   Grafo g=GRAFOinit();
   Vertice v1, v2;
   char label1[MAX], label2[MAX];
   int id1, id2, wt;

   while(fscanf(f, "%s %*d %s", label1, label2)==2){
      id1=STsearch(g->table, label1);
      if(id1==-1){
         v1=VERTICEcrea(label1);
         STinsert(g->table, v1);
         (g->V)++;
      }
      id2=STsearch(g->table, label2);
      if(id2==-1){
         v2=VERTICEcrea(label2);
         STinsert(g->table, v2);
         (g->V)++;
      }
   }
   rewind(f);
   g->matAdj=MATRIXinit(g->V, g->V, -1);
   while(fscanf(f, "%s %d %s", label1, &wt, label2)==3){
      id1=STsearch(g->table, label1);
      id2=STsearch(g->table, label2);
      if(id1!=-1 && id2!=-1){
         GRAFOinsertE(g, id1, id2, wt);
      }
   }
   return g;
}


void GRAFOinsertE(Grafo g, int id1, int id2, int wt){
    if(g->matAdj[id1][id2]==-1){
        g->matAdj[id1][id2]=wt;
        (g->E)++;
    }
}


void GRAFOintersezioneEStampaSottocammini(Grafo g, char *nomeFile, FILE *f){
   Cammino cammini[2];
   FILE *fi;
   int *intersezione1, *intersezione2, dim1, dim2, i;
   Vertice v;

   fi=fopen(nomeFile, "r");
   if(fi==NULL) exit(EXIT_FAILURE);

   cammini[0]=CAMMINOread(g->table, fi);
   cammini[1]=CAMMINOread(g->table, fi);

   fprintf(f, "I due cammini sono:\n");
   CAMMINOstampa(cammini[0], g->table, f);
   fprintf(f, "\n");
   CAMMINOstampa(cammini[1], g->table, f);
   printf("\n\n");

   intersezione1=CAMMINOintersezione(cammini[0], cammini[1], &dim1);
   intersezione2=CAMMINOintersezione(cammini[1], cammini[0], &dim2);

   if(dim1==0 && dim2==0)
      fprintf(f, "I due cammini non hanno vertici in comune.\n");
   else{
      fprintf(f, "I due cammini hanno i seguenti vertici in comune:\n");
      for(i=0; i<dim1; i++){
         v=STgetVerticeByIndex(g->table, intersezione1[i]);
         fprintf(f, "%s\n", v.nome);
      }
      fprintf(f, "\nIl cammino 1 si decompone in %d sottocammini:\n", dim1);
      CAMMINOstampaSottocammini(cammini[0], intersezione1, dim1, g->table, f);
      fprintf(f, "\nIl cammino 2 si decompone in %d sottocammini:\n", dim2);
      CAMMINOstampaSottocammini(cammini[1], intersezione2, dim2, g->table, f);
      printf("\n");
   }
   return;
}


static void pathMax(Grafo g, int v, int end, Cammino *sol, Cammino *bestSol, int k, int nVerticiRiat, int p, int nRiat, int *riatt, int *visited, int peso, int *max){
   int i, w;
   if(v==end){
      if(peso>(*max)){
         (*max)=peso;
         CAMMINOclear(bestSol);
         *bestSol=CAMMINOcrea(sol->dim);
         for(i=0; i<sol->dim; i++)
            CAMMINOinsert(bestSol, sol->vertici[i]);
      }
     return;
   }
   for(w=0; w<g->V; w++){
      if(g->matAdj[v][w]!=-1){
         if(visited[w]==0){
            visited[w]=1;
            CAMMINOinsert(sol, w);
            peso+=g->matAdj[v][w];
            pathMax(g, w, end, sol, bestSol, k, nVerticiRiat, p, nRiat, riatt, visited, peso, max);
            visited[w]=0;
            CAMMINOelimina(sol);
            peso-=g->matAdj[v][w];
         }
         else if(visited[w]==1 && nRiat<p){
            if(riatt[w]==0 && nVerticiRiat<k){
               nVerticiRiat++;
               riatt[w]=1;
               nRiat++;
               CAMMINOinsert(sol, w);
               peso+=g->matAdj[v][w];
               pathMax(g, w, end, sol, bestSol, k, nVerticiRiat, p, nRiat, riatt, visited, peso, max);
               nRiat--;
               peso-=g->matAdj[v][w];
               CAMMINOelimina(sol);
               nVerticiRiat--;
               riatt[w]=0;
             }
             else if(riatt[w]==1){
                nRiat++;
                CAMMINOinsert(sol, w);
                peso+=g->matAdj[v][w];
                pathMax(g, w, end, sol, bestSol, k, nVerticiRiat, p, nRiat, riatt, visited, peso, max);
                nRiat--;
                CAMMINOelimina(sol);
                peso-=g->matAdj[v][w];
             }
         }
      }
   }
   return;
}

void GRAFOsolve(Grafo g, int k, int p, char *inizio, char *fine){
   int  peso=0, max=0, nRiattraversamenti=0, nVerticiRiattraversati=0, *riatt;
   Cammino sol, bestSol;
   int *visited, start, end;

   if(STsearch(g->table, inizio)==-1 || STsearch(g->table, fine)==-1){
      printf("I vertici inseriti non sono validi.\n");
      return;
   }

   start=STsearch(g->table, inizio);
   end=STsearch(g->table, fine);

   sol=CAMMINOcrea(1);
   bestSol=CAMMINOcrea(1);

   riatt=calloc(g->V, sizeof(int));
   if(riatt==NULL) exit(EXIT_FAILURE);

   visited=calloc(g->V, sizeof(int));
   if(visited==NULL) exit(EXIT_FAILURE);

   CAMMINOinsert(&sol, start);
   visited[start]=1;
   pathMax(g, start, end, &sol, &bestSol, k, nVerticiRiattraversati, p, nRiattraversamenti, riatt, visited, peso, &max);

   printf("Vertice sorgente: %s - Vertice destinazione: %s - k: %d - p: %d\n", inizio, fine, k, p);
   printf("Best Solution:\n");
   printf("Peso Massimo: %d\n", max);
   printf("Cammino: ");
   CAMMINOstampa(bestSol, g->table, stdout);
   printf("\n");

   CAMMINOclear(&bestSol);
   CAMMINOclear(&sol);
   free(visited);
   free(riatt);
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
