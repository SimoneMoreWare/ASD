#include "grafo.h"

struct grafo{
    int V, E;
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
            mat[i][j]=value;
    return mat;
}


Grafo GRAPHinit(){
    Grafo g;
    g=(Grafo)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);
    g->V=0;
    g->E=0;
    g->matAdj=NULL;
    g->table=STinit(1);
    return g;
}


Grafo GRAPHload(FILE *f){
    Grafo g=GRAPHinit();
    char label1[MAX], label2[MAX];
    int id1, id2, wt;
    Vertice v, *v1, *v2;

    while(fscanf(f, "%s %*d %s", label1, label2)==2){
       id1=STgetVerticeByLabel(g->table, label1);
       id2=STgetVerticeByLabel(g->table, label2);
       if(id1==-1){
          v=VERTICEcrea(label1);
          STinsert(g->table, v);
          (g->V)++;
       }
       if(id2==-1){
          v=VERTICEcrea(label2);
          STinsert(g->table, v);
          (g->V)++;
       }
    }

    g->matAdj=MATRIXinit(g->V, g->V, -1);

    rewind(f);

    while(fscanf(f, "%s %d %s", label1, &wt, label2)==3){
       id1=STgetVerticeByLabel(g->table, label1);
       id2=STgetVerticeByLabel(g->table, label2);
       if(id1!=-1 && id2!=-1){
          GRAPHinsertE(g, id1, id2, wt);
          v1=STgetVerticeByIndex(g->table, id1);
          VERTICEincrementaOutDegree(v1);
          v2=STgetVerticeByIndex(g->table, id2);
          VERTICEincrementaInDegree(v2);
       }
    }
    return g;
}


void GRAPHinsertE(Grafo g, int id1, int id2, int wt){
    if(g->matAdj[id1][id2]==-1){
        g->matAdj[id1][id2]=wt;
        (g->E)++;
    }
    return;
}


Boolean GRAPHisRegular(Grafo g){
    int i;
    Vertice *v;
    for(i=0; i<g->V; i++){
       v=STgetVerticeByIndex(g->table, i);
       if(v->inDegree!=v->outDegree){
          return FALSO;
       }
    }
    return VERO;
}


static void path(Grafo g, int v, int lun, int peso, int *max, int *visited, int *sol, int *bestSol, int *bestLun){
    Boolean fine=VERO;
    int i, w;

    visited[v]=1;

    for(w=0; w<g->V; w++){
       if(g->matAdj[v][w]!=-1 && visited[w]==0){
          sol[lun]=w;
          peso=peso+g->matAdj[v][w];
          path(g, w, lun+1, peso, max, visited, sol, bestSol, bestLun);
          fine=FALSO;
          peso=peso-g->matAdj[v][w];
       }
    }
    if(fine==VERO){
       if(peso>(*max)){
          (*max)=peso;
          (*bestLun)=lun;
          for(i=0; i<lun; i++)
             bestSol[i]=sol[i];
       }
       return;
    }
    visited[v]=0;
    return;
}


void GRAPHcamminoMassimo(Grafo g, char *sorgente){
    int idSorgente, max=0, bestLun=0;
    int *sol, *bestSol, *visited, i;

    idSorgente=STgetVerticeByLabel(g->table, sorgente);

    if(idSorgente==-1){
       printf("\nIl vertice %s non esiste.\n", sorgente);
       return;
    }

    sol=(int*)malloc(g->V*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int*)malloc(g->V*sizeof(int));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    visited=(int*)malloc(g->V*sizeof(int));
    if(visited==NULL) exit(EXIT_FAILURE);

    for(i=0; i<g->V; i++)
       visited[i]=0;

    path(g, idSorgente, 0, 0, &max, visited, sol, bestSol, &bestLun);

    if(bestLun==0){
        printf("\nNon esiste alcun cammino semplice con sorgente nel vertice %s per il quale la somma dei pesi degli archi e' massima.\n", sorgente);
        return;
    }
    printf("\nBest Solution:\n");
    printf("Peso massimo: %d\n", max);
    printf("Percorso: ");
    printf("(%d, %d) con peso: %d", idSorgente, bestSol[0], g->matAdj[idSorgente][bestSol[0]]);
    for(i=0; i<(bestLun-1); i++){
       printf(" - (%d, %d) con peso: %d %s ", bestSol[i], bestSol[i+1], g->matAdj[bestSol[i]][bestSol[i+1]], (i==bestLun-2)?"":"-");
    }
    printf("\n");
    return;
}


static void MATRIXfree(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            if(mat[i]!=NULL){
                free(mat[i]);
            }
        }
        free(mat);
    }
    return;
}


void GRAPHfree(Grafo g){
    if(g!=NULL){
        STfree(g->table);
        MATRIXfree(g->matAdj, g->V);
        free(g);
    }
}
