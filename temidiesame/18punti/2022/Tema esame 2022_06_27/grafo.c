#include "grafo.h"

struct grafo{
   int V, E;
   int **matAdj;
};

static int **MATRIXinit(int nr, int nc, int value){
    int **mat, i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL)
        exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL)
            exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            mat[i][j]=value;
    return mat;
}


Grafo GRAFOinit(int V){
    Grafo g;
    g=(Grafo)malloc(sizeof(struct grafo));
    if(g==NULL)
        exit(EXIT_FAILURE);
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


static Boolean isDominatingSet(Grafo g, int *proposta, int partizione){
    int vertice, id, count;

    for(vertice=0; vertice<g->V; vertice++){
       if(proposta[vertice]!=partizione){
          count=0;
          for(id=0; id<g->V; id++){
             if(g->matAdj[vertice][id]!=-1 && proposta[id]==partizione){
                count++;
                break;
             }
          }
          if(count==0)
             return FALSO;
       }
    }
    return VERO;
}


//Formato file:
//1 riga: numero partizioni
//Ogni riga (che corrisponde alla partizione i-esima) contiene il numero dei vertici della partizione seguito dai vertici
Boolean GRAFOcheck(Grafo g, char *nomeFile){
    FILE *f;
    int partizione, nPartizioni, vertice, nVerticiPartizione, i;
    int *proposta;

    f=fopen(nomeFile, "r");
    if(f==NULL)
       exit(EXIT_FAILURE);

    proposta=calloc(g->V, sizeof(int));
    if(proposta==NULL)
       exit(EXIT_FAILURE);

    fscanf(f, "%d", &nPartizioni);
    if(nPartizioni>g->V)
       return FALSO;
    for(partizione=1; partizione<=nPartizioni; partizione++){
       fscanf(f, "%d", &nVerticiPartizione);
       for(i=0; i<nVerticiPartizione; i++){
          fscanf(f, "%d", &vertice);
          //non è un vertice del grafo
          if(vertice<0 || vertice>=g->V)
             return FALSO;
          //il vertice appartiene gia ad un altro insieme
          if(proposta[vertice]!=0)
             return FALSO;
          proposta[vertice]=partizione;
       }
    }

    //tutti i vertici devono appartenere ad una partizione
    for(i=0; i<g->V; i++)
       if(proposta[i]==0)
          return FALSO;

    for(i=1; i<=nPartizioni; i++)
    	if(isDominatingSet(g, proposta, i)==FALSO)
            return FALSO;
    return VERO;
}


static Boolean isDomaticPartition (Grafo g, int *sol, int nPart){
    int i;
    for(i=1; i<=nPart; i++){
       if(isDominatingSet(g, sol, i)==FALSO)
          return FALSO;
    }
    return VERO;
}


static int getNumPartizioni(int *sol, int dim){
    int *occPart, i, count=0;

    occPart=calloc(dim, sizeof(int));
    if(occPart==NULL) exit(EXIT_FAILURE);

    for(i=0; i<dim; i++){
       occPart[sol[i]-1]++;
    }

    for(i=0; i<dim; i++)
       if(occPart[i]!=0)
          count++;
    free(occPart);
    return count;
}


static void solveR(Grafo g, int *sol, int *bestSol, int *bestLun, int pos){
    int i, nPart, j;
    if(pos>=g->V){
       nPart=getNumPartizioni(sol, g->V);
       if(nPart>(*bestLun) && isDomaticPartition(g, sol, nPart)==VERO){
          (*bestLun)=nPart;
          for(j=0; j<g->V; j++)
              bestSol[j]=sol[j];
       }
       return;
    }
    for(i=1; i<=g->V; i++){
       sol[pos]=i;
       solveR(g, sol, bestSol, bestLun, pos+1);
    }
    return;
}


void GRAFOsolve(Grafo g){
    int *sol, *bestSol, bestLun=0, partizione, vertice;

    sol=(int *)malloc(g->V*sizeof(int));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(int*)malloc(g->V*sizeof(int));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    solveR(g, sol, bestSol, &bestLun, 0);

    printf("Best Solution:\n");
    printf("V = {");
    for(partizione=1; partizione<=bestLun; partizione++){
        printf("\n       V%d = { ", partizione);
        for(vertice=0; vertice<g->V; vertice++){
            if(bestSol[vertice]==partizione){
               printf("v%d ", vertice);
            }
        }
        printf("} ");
    }
    printf("\n     }\n");
    free(sol);
    free(bestSol);
    return;
}


static void MATRIXifree(int **mat, int nr){
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
        MATRIXifree(g->matAdj, g->V);
        free(g);
    }
}



void GRAFOprint(Grafo g, FILE *f){
    int i, j;
    for(i=0; i<g->V; i++){
        fprintf(f, "Vertice: %d - Archi: ", i);
        for(j=0; j<g->V; j++){
            if(g->matAdj[i][j]!=-1)
                fprintf(f, "(%d, %d) ", i, j);
        }
        fprintf(f, "\n");
    }
}
