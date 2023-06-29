#include "grafo.h"

struct grafo{
      int V, E;
      int **matAdj;
      Cicli c;
};

//funzioni standard;
static int **MATRIXinit(int nr, int nc, int val){
    int **m;
    int i, j;
    m=(int**)malloc(nr*sizeof(int*));
    if(m==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        m[i]=(int*)malloc(nc*sizeof(int));
        if(m[i]==NULL) exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            m[i][j]=val;
    return m;
}

static void free2D(int **m, int nr){
    int i;
    if(m!=NULL){
        for(i=0; i<nr; i++)
            free(m[i]);
        free(m);
    }
}


Graph GRAPHinit(int V){
	Graph g;
    g=(Graph)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);
    g->V=V;
    g->E=0;
    g->matAdj=MATRIXinit(V, V, -1);
    g->c=NULL;
    return g;
}

Graph GRAPHload(FILE *f){
    Graph g;
    int V, E, i, id1, id2;
    fscanf(f, "%d %d", &V, &E);
    g=GRAPHinit(V);
    g->E=E;
    for(i=0; i<E; i++){
        fscanf(f, "%d %d", &id1, &id2);
        if(id1>=0 && id1<V && id2>=0 && id2<V)
            GRAPHinsertEdge(g, id1, id2);
    }
    return g;
}

void GRAPHinsertEdge(Graph g, int v, int w){
    if(g->matAdj[v][w]==-1){
        g->matAdj[v][w]=1;
    }
}

void GRAPHreadCicli(Graph g, FILE *f){
    g->c=CICLIread(f);
    return;
}

void GRAPHfree(Graph g){
    if(g!=NULL){
        if(g->matAdj!=NULL)
            free2D(g->matAdj, g->V);
        if(g->c!=NULL)
            CICLIfree(g->c);
        free(g);
    }
}

//il file è organizzato cosi: sulla prima riga c'è il numero di vertici NVERTICI, sulla seconda riga ci sono NVERTICI numeri interi
Boolean GRAPHverifica(Graph g, FILE *f){
	Ciclo c=CICLOread(f);
    int i;
    for(i=0; i<c.nVertici; i++){
        if(c.vertici[i]<0 || c.vertici[i]>=g->V)
                return FALSO;
        if(i>0){
            if(g->matAdj[c.vertici[i-1]][c.vertici[i]]==-1)
                return FALSO;
        }
    }
    if(g->matAdj[c.vertici[c.nVertici-1]][c.vertici[0]]==-1)
		return FALSO;
    return VERO;
}

static Boolean copreVertici(int V, Ciclo *sol, int dim){
	int *vertici=calloc(V, sizeof(int));
    int i, j;
    for(i=0; i<dim; i++){
        for(j=0; j<sol[i].nVertici; j++){
            vertici[sol[i].vertici[j]]++;
        }
    }
    for(i=0; i<V; i++){
        if(vertici[i]==0)
            return FALSO;
    }
    return VERO;
}

static Boolean isDisgiunto(int V, Ciclo *sol, int dim){
    int *vertici=calloc(V, sizeof(int));
    int i, j;
    for(i=0; i<dim; i++){
        for(j=0; j<sol[i].nVertici; j++){
           vertici[sol[i].vertici[j]]++;
        }
    }
    for(i=0; i<V; i++){
        if(vertici[i]>1)
           return FALSO;
    }
    return VERO;
}

static Boolean powerSetR(Graph g, int nCicli, Ciclo *sol, int pos, int start, int dimInsieme){
     int i;

     if(pos>=dimInsieme){
         if(copreVertici(g->V, sol, pos)==VERO && isDisgiunto(g->V, sol, pos)==VERO){
              return VERO;
         }
         return FALSO;
     }

     for(i=start; i<nCicli; i++){
         sol[pos]=CICLIgetCiclo(g->c, i);
         if(powerSetR(g, nCicli, sol, pos+1, start+1, dimInsieme)==VERO)
            return VERO;
     }
     return FALSO;
}

void GRAPHsolve(Graph g){
    FILE *f=fopen("cicli.txt", "r");
    int nCicli, k, i;
    Ciclo *sol;
    Boolean trovato;

    if(f==NULL) exit(EXIT_FAILURE);
    GRAPHreadCicli(g, f);

    nCicli=CICLIgetNumCicli(g->c);

    sol=(Ciclo*)malloc(nCicli*sizeof(Ciclo));
    if(sol==NULL) exit(EXIT_FAILURE);

    for(k=1; k<=nCicli; k++){
        trovato=powerSetR(g, nCicli, sol, 0, 0, k);
        if(trovato==VERO){
            break;
        }
    }
    if(trovato==VERO){
        printf("Best solution:\n");
        for(i=0; i<k; i++){
            CICLOprint(sol[i], stdout);
            printf("\n");
        }
    }
    else{
        printf("Soluzione non trovata.\n");
    }

    free(sol);
    return;
}


