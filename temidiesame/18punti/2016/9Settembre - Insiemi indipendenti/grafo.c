/*   grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:54
*/
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "st.h"


struct grafo{int V,E; int **madj; ST table;};

static Edge EdgeCreate(int v, int w);
static void insertE(Graph g, Edge e);
static void removeE(Graph G, Edge e);


int GRAPHgetE(Graph G){
    return G->E;
}

int GRAPHgetV(Graph G){
    return G->V;
}

Graph GRAPHinit(int V){
    int i;
    Graph g;
    g = malloc(sizeof(*g));
    g->V = V;
    g->E = 0;
    g->madj = malloc(V* sizeof(int*));
    for(i=0; i<V; i++)
        g->madj[i] = calloc(V, sizeof(int));
    return g;
}

void GRAPHfree(Graph g){
    int i;
    for(i=0; i < g->V; i++) {
        free(g->madj[i]);
    }
    free(g->madj);
    free(g);
}

static Edge EdgeCreate(int v, int w){
    Edge e;
    e.v = v;
    e.w = w;
    return e;
}

void GRAPHinsertE(Graph G, int id1, int id2){
    insertE(G, EdgeCreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2){
    removeE(G,EdgeCreate(id1,id2));
}

Graph readFile(FILE *in){
    int i,n,j;
    char id1[30], id2[30];
    ST st;
    Graph G;
    st = STinit(16);
    while(fscanf(in, "%s %s", id1, id2) == 2){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        if(i==-1) STinsert(st, id1);
        if(j==-1) STinsert(st, id2);
    }
    n = STgetN(st);
    G = GRAPHinit(n);
    rewind(in);
    while(fscanf(in,"%s %s\n",id1,id2) == 2){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        GRAPHinsertE(G,i,j);
    }
    G->table = st;
    return G;
}

Graph GRAPHreadFile(FILE *in){
    return readFile(in);
}

static void removeE(Graph G, Edge e){
    int v = e.v, w = e.w;
    if(G->madj[v][w] != 0){
        G->madj[v][w] = 0;
        G->E--;
    }
}

static void insertE(Graph g, Edge e){
    int v = e.v, w = e.w;
    if(g->madj[v][w] == 0)
        g->E++;
    g->madj[v][w] = 1;
    g->madj[w][v] = 1;
}

void GRAPHprintmatrix(Graph G){
    int i,j;
    for(i=0; i<G->V; i++){
        for(j=0; j <G->V; j++)
            printf("%3d ",G->madj[i][j]);
        printf("\n");
    }
}


int GRAPHedges(Graph G, int *v, int i){
    int j,n=0;
    for(j=0; j<G->V; j++)
        if(G->madj[i][j] != 0)
            v[n++] = j;
    return n;
}

int *readSet(FILE *in, Graph G, int *dim){
    int j, *sol;
    char id[31];
    sol = malloc(G->V* sizeof(int));
    while(fscanf(in, "%s", id) == 1){
        j = STsearchbyname(G->table, id);
        sol[(*dim)++] = j;
    }
    return sol;
}

int isIndipendent(Graph G, int *sol, int dim){
    int i,j;
    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            if(G->madj[sol[i]][sol[j]] == 1)
                return 0;
        }
    }
    return 1;
}

static int appartiene(int *sol, int dim, int index){
    int i;
    for(i=0; i<dim; i++)
        if(sol[i] == index)
            return 1;
    return 0;
}

static int isMaximalIndipendent(Graph G, int *sol, int dim){
    int i;
    for(i=0; i<G->V; i++){
        if(!appartiene(sol, dim, i)){
            sol[dim++] = i;
            if(isIndipendent(G, sol, dim))
                return 0;
            dim--;
        }
    }
    return 1;
}

static int combinazioni(int pos, int *sol, Graph G, int start, int l){
    int i;
    if(pos == l){
        if(isMaximalIndipendent(G, sol, l))
            return 1;
        return 0;
    }
    for(i=start; i <G->V; i++){
        sol[pos] = i;
        if(combinazioni(pos+1, sol, G, i+1, l))
            return 1;
    }
    return 0;
}

void generaMaximalIndipendentSet(FILE *out, Graph G){
    int *sol, i, l, trovata = 0;
    sol = malloc(G->V* sizeof(int));
    for(i=1; i<G->V && trovata == 0; i++){
        trovata = combinazioni(0, sol, G, 0, i);
    }
    l = i;
    if(!trovata)
        printf("Insieme indipendente massimale non trovato.\n");
    else{
        printf("Numero di indipendenza: %d\n", l);
        for(i=0; i<l; i++)
            fprintf(out, "%s\n", STgetbyindex(G->table, sol[i]));
    }

}
