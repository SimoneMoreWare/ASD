#include "grafo.h"
#include <math.h>
#include <limits.h>

struct grafo{
    int V, E;
    float **matAdj;
    ST table;
};



//EDGE
Edge EDGEcreate(int id1, int id2, float wt){
    Edge e;
    e.v=id1;
    e.w=id2;
    e.wt=wt;
    return e;
}


void EDGEinsert(Edge *e, int *dim, int *maxD, Edge a){
    if((*maxD) == (*dim)){
        (*maxD)=(*maxD) * 2;
        e=realloc(e, (*maxD)*sizeof(Edge));
        if(e==NULL) exit(EXIT_FAILURE);
    }
    e[(*dim)]=a;
    (*dim)++;
    return;
}


Boolean EDGEisPresente(Edge *archi, int dim, Edge e){
    int i;
    for(i=0; i<dim; i++){
        if((archi[i].v==e.v && archi[i].w==e.w) || (archi[i].v==e.w && archi[i].w==e.v))
            return VERO;
    }
    return FALSO;
}



//GRAFO
static float **MATRIXinit(int nr, int nc, float value){
    float **mat;
    int i, j;
    mat=(float**)malloc(nr*sizeof(float*));
    if(mat==NULL)
        exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(float*)malloc(nc*sizeof(float));
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
    g->table=STinit(V);
    g->matAdj=MATRIXinit(g->V, g->V, -1);
    return g;
}


Grafo GRAFOload(FILE *f){
    int V, i, id, id1;
    float wt;
    Grafo g;
    Vertice v, v1;
    char label[CAR], label1[CAR];

    fscanf(f, "%d", &V);
    g=GRAFOinit(V);
    for(i=0; i<V; i++){
       v=VERTICEread(f);
       STinsert(g->table, v);
    }

    while(fscanf(f, "%s %s", label, label1)==2){
        id=STsearch(g->table, label);
        id1=STsearch(g->table, label1);
        if(id!=-1 && id1!=-1){
           v=STgetByIndex(g->table, id);
           v1=STgetByIndex(g->table, id1);
           wt=sqrt(pow((v1.x-v.x), 2) + pow((v1.y-v.y), 2));
           GRAFOinsertE(g, id, id1, wt);
        }
    }
    return g;
}


void GRAFOinsertE(Grafo g, int id1, int id2, float wt){
    if(g->matAdj[id1][id2]==-1){
       g->matAdj[id1][id2]=wt;
       g->matAdj[id2][id1]=wt;
       (g->E)++;
    }
    return;
}


void GRAFOdeleteE(Grafo g, int id1, int id2){
    if(g->matAdj[id1][id2]!=-1){
       g->matAdj[id1][id2]=-1;
       g->matAdj[id2][id1]=-1;
       (g->E)--;
    }
    return;
}


Edge *GRAFOreadProposta(Grafo g, char *nomeFile, int *nArchi){
     FILE *f;
     int id, id1;
     Edge *archi;
     float wt;
     int maxD=1, indexA=0;
     char label[CAR], label1[CAR];
     Vertice v, v1;

     f=fopen(nomeFile, "r");
     if(f==NULL) exit(EXIT_FAILURE);

     archi=(Edge*)malloc(maxD*sizeof(Edge));
     if(archi==NULL) exit(EXIT_FAILURE);

     while(fscanf(f, "%s %s", label, label1)==2){
         id=STsearch(g->table, label);
         id1=STsearch(g->table, label1);
         if(id!=-1 && id1!=-1){
            v=STgetByIndex(g->table, id);
            v1=STgetByIndex(g->table, id1);
            wt=sqrt(pow((v1.x-v.x), 2) + pow((v1.y-v.y), 2));
            if(maxD==indexA){
               maxD=2*maxD;
               archi=realloc(archi, maxD*sizeof(Edge));
               if(archi==NULL) exit(EXIT_FAILURE);
            }
            archi[indexA++]=EDGEcreate(id, id1, wt);
         }
     }
     (*nArchi)=indexA;
     return archi;
}


static Boolean pathR(Grafo g, int vertice, int end, int *visited){
    int i;
    if(vertice==end){
       return VERO;
    }
    visited[vertice]=1;
    for(i=0; i<g->V; i++){
       if(visited[i]==0 && g->matAdj[vertice][i]!=-1){
          if(pathR(g, i, end, visited)==VERO)
             return VERO;
       }
    }
    return FALSO;
}


Boolean GRAFOisConnesso(Grafo g){
    int *visited, v1, v2;

    for(v1=0; v1<g->V; v1++){
       for(v2=0; v2<g->V; v2++){
          if(v1!=v2){
              visited=calloc(g->V, sizeof(int));
              if(visited==NULL) exit(EXIT_FAILURE);
              if(pathR(g, v1, v2, visited)==FALSO)
                 return FALSO;
              free(visited);
          }
       }
    }

    return VERO;
}


static void pathMinR(Grafo g, int vertice, int end, int *visited, float wt, int lun, float *minimo, int *bestLun){
    int i;

    visited[vertice]=1;

    for(i=0; i<g->V; i++){
       if(g->matAdj[vertice][i]!=-1 && visited[i]==0 && wt+g->matAdj[vertice][i]<=(*minimo)){
          wt=wt+g->matAdj[vertice][i];
          pathMinR(g, i, end, visited, wt, lun+1, minimo, bestLun);
          wt=wt-g->matAdj[vertice][i];
       }
    }

    if(vertice==end){
       if(wt < (*minimo)){
          (*minimo) = wt;
          (*bestLun) = lun;
       }
    }
    visited[vertice]=0;
    return;
}


int GRAFOgetDiametro(Grafo g){
   int diametro=0, vertice, end, *visited, bestLun;
   float min;

   visited=calloc(g->V, sizeof(int));
   if(visited==NULL) exit(EXIT_FAILURE);

  for(vertice=0; vertice<g->V; vertice++){
      for(end=0; end<g->V; end++){
        if(vertice!=end){
            min=INT_MAX;
            pathMinR(g, vertice, end, visited, 0, 0, &min, &bestLun);
            if(bestLun > diametro)
                  diametro=bestLun;
           }
        }
   }
   free(visited);
   return diametro;
}


Boolean GRAFOcheckProposta(Grafo g, Edge *proposta, int nArchi, int *diametro){
    int i;
    for(i=0; i<nArchi; i++)
       GRAFOinsertE(g, proposta[i].v, proposta[i].w, proposta[i].wt);

    if(GRAFOisConnesso(g)==FALSO){
        for(i=0; i<nArchi; i++)
            GRAFOdeleteE(g, proposta[i].v, proposta[i].w);
        return FALSO;
    }

    (*diametro)=GRAFOgetDiametro(g);

    for(i=0; i<nArchi; i++)
       GRAFOdeleteE(g, proposta[i].v, proposta[i].w);

    return VERO;
}


void GRAFOcheckProposte(Grafo g, char *nomeFile1, char *nomeFile2){
    Edge *proposta1, *proposta2;
    int nArchi1, nArchi2, diametro1=-1, diametro2=-1;

    proposta1=GRAFOreadProposta(g, nomeFile1, &nArchi1);
    proposta2=GRAFOreadProposta(g, nomeFile2, &nArchi2);

    if(GRAFOcheckProposta(g, proposta1, nArchi1, &diametro1)==FALSO){
       printf("La proposta presente nel file %s non e' valida. Il grafo non risulta connesso.\n\n", nomeFile1);
    }

    if(GRAFOcheckProposta(g, proposta2, nArchi2, &diametro2)==FALSO){
       printf("La proposta presente nel file %s non e' valida. Il grafo non risulta connesso.\n\n", nomeFile2);
    }

    if(diametro1==-1 && diametro2==-1)
       return;

    if((diametro1==-1 && diametro2!=-1) || (diametro1!=-1 && diametro2!=-1 && diametro2<diametro1)){
       printf("Il diametro inferiore e' %d ed e' ottenuto dall'insieme di archi presente in %s.\n\n", diametro2, nomeFile2);
    }
    else if((diametro2==-1 && diametro1!=-1) || (diametro1!=-1 && diametro2!=-1 && diametro1<diametro2)){
       printf("Il diametro inferiore e' %d ed e' ottenuto dall'insieme di archi presente in %s.\n\n", diametro1, nomeFile1);
    }

    free(proposta1);
    free(proposta2);
    return;
}


static void freeMATRIX(float **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++)
            if(mat[i]!=NULL)
                free(mat[i]);
        free(mat);
    }
    return;
}


static void powerSet(Grafo g, Edge *val, int dim, Edge *sol, Edge *bestSol, int *min, int dimInsieme, Boolean *trovato, int pos, int start){
    int diametro, i, j;
    if(pos>=dimInsieme){
        if(GRAFOcheckProposta(g, sol, dimInsieme, &diametro)==VERO && diametro <(*min)){
            (*trovato)=VERO;
            (*min)=diametro;
            for(j=0; j<dimInsieme; j++){
                bestSol[j]=sol[j];
            }
        }
        return;
    }
    for(i=start; i<dim; i++){
        sol[pos]=val[i];
        powerSet(g, val, dim, sol, bestSol, min, dimInsieme, trovato, pos+1, i+1);
    }
    return;
}


void GRAFOsolve(Grafo g){
    Edge *archiAssenti, e, *sol, *bestSol;
    int dim=0, maxD=10, v, w, k, i;
    Vertice v1, v2;
    int min=INT_MAX;
    float wt;
    Boolean trovato=FALSO;

    archiAssenti=(Edge*)malloc(maxD*sizeof(Edge));
    if(archiAssenti==NULL) exit(EXIT_FAILURE);

    for(v=0; v<g->V; v++){
        for(w=0; w<g->V; w++){
            if(v!=w && g->matAdj[v][w]==-1){
                v1=STgetByIndex(g->table, v);
                v2=STgetByIndex(g->table, w);
                wt=sqrt(pow((v2.x-v1.x), 2) + pow((v2.y-v1.y), 2));
                e=EDGEcreate(v, w, wt);
                if(EDGEisPresente(archiAssenti, dim, e)==FALSO){
                    EDGEinsert(archiAssenti, &dim, &maxD, e);
                }
            }
        }
    }

    sol=(Edge*)malloc(dim*sizeof(Edge));
    if(sol==NULL) exit(EXIT_FAILURE);

    bestSol=(Edge*)malloc(dim*sizeof(Edge));
    if(bestSol==NULL) exit(EXIT_FAILURE);

    for(k=1; k<=dim; k++){
        powerSet(g, archiAssenti, dim, sol, bestSol, &min, k, &trovato, 0, 0);
        if(trovato==VERO)
            break;
    }

    printf("Best Solution:\n");
    for(i=0; i<k; i++){
        v1=STgetByIndex(g->table, bestSol[i].v);
        v2=STgetByIndex(g->table, bestSol[i].w);
        printf("(%s, %s)\n", v1.id, v2.id);
    }
    printf("Diametro minimo: %d - Cardinalita minima: %d\n", min, k);

    free(sol);
    free(bestSol);
    free(archiAssenti);
    return;
}


void GRAFOfree(Grafo g){
    if(g!=NULL){
        STfree(g->table);
        freeMATRIX(g->matAdj, g->V);
        free(g);
    }
    return;
}

