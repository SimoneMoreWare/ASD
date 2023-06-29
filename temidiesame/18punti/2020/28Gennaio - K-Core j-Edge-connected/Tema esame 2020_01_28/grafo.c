#include "grafo.h"

struct grafo{
    int V, E;
    ST table;
    int **matAdj;
    Vertice *eliminati;
    int nEliminati, maxD;
};



//Edge
Edge EDGEcreate(int v, int w){
    Edge e;
    e.v=v;
    e.w=w;
    return e;
}


Simboli EDGEcompare(Edge e1, Edge e2){
    if((e1.v==e2.v || e1.v==e2.w) && (e1.w==e2.v || e1.w==e2.w))
        return UGUALE;
    return DIVERSO;
}



//Grafo
int **MATRIXinit(int nr, int nc, int value){
    int **mat;
    int i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL){
            printf("Errore di allocazione.");
            exit(EXIT_FAILURE);
        }
    }
    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            mat[i][j]=value;
    return mat;
}


Graph GRAPHinit(int V){
    Graph g;
    g=(Graph)malloc(sizeof(struct grafo));
    if(g==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    g->E=0;
    g->V=V;
    g->table=STinit(g->V);
    g->matAdj=MATRIXinit(g->V, g->V, -1);
    g->nEliminati=0;
    g->maxD=1;
    g->eliminati=(Vertice*)malloc(g->maxD*sizeof(Vertice));
    if(g->eliminati==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    return g;
}


Graph GRAPHload(FILE *f){
    Graph g;
    int V, i, id, id1;
    char label[11], label1[11];
    fscanf(f, "%d", &V);
    g=GRAPHinit(V);
    for(i=0; i<V; i++){
        fscanf(f, "%s", label);
        STinsert(g->table, VERTICEcrea(label));
    }
    while(fscanf(f, "%s %s", label, label1)==2){
        id=STsearchByName(g->table, label);
        id1=STsearchByName(g->table, label1);
        if(id!=-1 && id1!=-1){
            GRAPHinsertE(g, id, id1);
        }
    }
    return g;
}


void GRAPHinsertE(Graph g, int id1, int id2){
    Vertice *v1, *v2;
    if(g->matAdj[id1][id2]==-1){
        (g->E)++;
        g->matAdj[id1][id2]=1;
        g->matAdj[id2][id1]=1;
        v1=STsearchByIndex(g->table, id1);
        v2=STsearchByIndex(g->table, id2);
        (v1->grado)++;
        (v2->grado)++;
    }
    return;
}


void GRAPHdeleteE(Graph g, int id1, int id2){
    Vertice *v1, *v2;
    if(g->matAdj[id1][id2]!=-1){
        (g->E)--;
        g->matAdj[id1][id2]=-1;
        g->matAdj[id2][id1]=-1;
        v1=STsearchByIndex(g->table, id1);
        v2=STsearchByIndex(g->table, id2);
        (v1->grado)--;
        (v2->grado)--;
    }
    return;
}


Boolean GRAPHkCore(Graph g, int k){
    int i, j;
    Vertice *v1, *v2;
    i=0;
    while(i<g->V){
       v1=STsearchByIndex(g->table, i);
       if(v1->grado<k && GRAPHisEliminato(g, *v1)==FALSO){
          GRAPHaddEliminati(g, *v1);
          for(j=0; j<g->V; j++){
             if(g->matAdj[i][j]!=-1){
                g->matAdj[i][j]=-1;
                g->matAdj[j][i]=-1;
                v2=STsearchByIndex(g->table, j);
                (v2->grado)--;
             }
          }
          i=0;
       }
       else{
          i++;
	 }
    }

    if(g->nEliminati==g->V)
       return FALSO;
    return VERO;
}


void GRAPHaddEliminati(Graph g, Vertice v){
    if(g->nEliminati==g->maxD){
       g->maxD=2*g->maxD;
       g->eliminati=realloc(g->eliminati, g->maxD*sizeof(Vertice));
       if(g->eliminati==NULL)
          exit(EXIT_FAILURE);
    }
    g->eliminati[g->nEliminati]=v;
    (g->nEliminati)++;
    return;
}


Boolean GRAPHisEliminato(Graph g, Vertice v){
    int i;
    for(i=0; i<g->nEliminati; i++){
       if(strcmp(g->eliminati[i].nome, v.nome)==0)
          return VERO;
    }
    return FALSO;
}


void GRAPHverticiKCorePrint(Graph g, FILE *f){
    int i;
    Vertice *v;
    for(i=0; i<g->V; i++){
       v=STsearchByIndex(g->table, i);
       if(GRAPHisEliminato(g, *v)==FALSO){
          VERTICEprint(*v, f);
          fprintf(f, "\n");
       }
    }
    return;
}


Boolean GRAPHarcoExist(Edge *archi, Edge e, int dim){
    int i;
    for(i=0; i<dim; i++){
        if(EDGEcompare(archi[i], e)==UGUALE)
            return VERO;
    }
    return FALSO;
}


Edge *GRAPHedges(Graph g){
    Edge *archi;
    int nArchi=0, i, j;
    archi=(Edge*)malloc((g->E)*sizeof(Edge));
    if(archi==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    for(i=0; i<g->V; i++){
        for(j=0; j<g->V; j++){
            if(g->matAdj[i][j]!=-1){
                if(GRAPHarcoExist(archi, EDGEcreate(i, j), nArchi)==FALSO){
                    archi[nArchi]=EDGEcreate(i, j);
                    nArchi++;
                }
            }
        }
    }
    return archi;
}

static Boolean pathR(Graph g, int end, int v, int *visited){
    int w;
    visited[v]=1;
    if(v==end){
        return VERO;
    }
    for(w=0; w<g->V; w++){
        if(g->matAdj[v][w]!=-1 && visited[w]==0){
            if(pathR(g, end, w, visited)==VERO)
                return VERO;
        }
    }
    return FALSO;
}


Boolean GRAPHisConnesso(Graph g){
    int start, end, *visited;
    for(start=0; start<(g->V-1); start++){
        for(end=start+1; end<g->V; end++){
            visited=calloc(g->V, sizeof(int));
            if(visited==NULL){
                printf("Errore di allocazione.");
                exit(EXIT_FAILURE);
            }
            if(pathR(g, end, start, visited)==FALSO)
                return FALSO;
            free(visited);
        }
    }
    return VERO;
}


static void powerSetR(Graph g, Edge *archi, int nArchi, Boolean *connesso, int *sol, int pos, int start, int dimInsieme){
    int i, j;
    Edge e;
    if(pos>=dimInsieme){
        for(j=0; j<dimInsieme; j++){
            e=archi[sol[j]];
            GRAPHdeleteE(g, e.v, e.w);
        }

        if(GRAPHisConnesso(g)==FALSO){
            *connesso=FALSO;
        }

        for(j=0; j<dimInsieme; j++){
            e=archi[sol[j]];
            GRAPHinsertE(g, e.v, e.w);
        }
        return;
    }
    for(i=start; i<nArchi; i++){
        sol[pos]=i;
        powerSetR(g, archi, nArchi, connesso, sol, pos+1, i+1, dimInsieme);
        if((*connesso)==FALSO){
            return;
        }
    }
    return;
}


void GRAPHjConnected(Graph g, int j){
    Edge *archi=GRAPHedges(g);
    int k, i;
    int *sol;
    Vertice *v, *w;
    Boolean connesso=VERO;;

    sol=(int *)malloc(g->E*sizeof(int));
    if(sol==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }

    //Controllo se esistono insiemi di archi di cardinalità < j in grado di sconnettere il grafo.
    //Se esistono allora il grafo non è j-edge-connected.
    for(k=1; k<j; k++){
        powerSetR(g, archi, g->E, &connesso, sol, 0, 0, k);
        if(connesso==FALSO){
            printf("\nIl grafo non e' %d-edge-connected.\n", j);
            return;
        }
    }

    powerSetR(g, archi, g->E, &connesso, sol, 0, 0, j);
    if(connesso==FALSO){
        printf("\nSottoinsieme di archi di cardinalita' %d che lo sconnette:\n", j);
        for(i=0; i<j; i++){
            v=STsearchByIndex(g->table, archi[sol[i]].v);
            w=STsearchByIndex(g->table, archi[sol[i]].w);
            VERTICEprint(*v, stdout);
            printf(" - ");
            VERTICEprint(*w, stdout);
            printf("\n");
        }
    }
    else{
       printf("\nNon esiste alcun sottoinsieme di archi di cardinalita' %d che lo sconnette.\n", j);
    }

    return;
}
