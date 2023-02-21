/*   grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:41:16
*/
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "st.h"


struct grafo{int V,E; int **madj; ST table;};

static Edge EdgeCreate(int v, int w, int wt);
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

static Edge EdgeCreate(int v, int w, int wt){
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt){
    insertE(G, EdgeCreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2, int wt){
    removeE(G,EdgeCreate(id1,id2, wt));
}

Graph readFile(FILE *in){
    int i,n,j, wt;
    char id1[30], id2[30];
    ST st;
    Graph G;
    st = STinit(16);
    while(fscanf(in, "%s %d %s", id1, &wt, id2) == 3){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        if(i==-1) STinsert(st, id1);
        if(j==-1) STinsert(st, id2);
    }
    n = STgetN(st);
    G = GRAPHinit(n);
    rewind(in);
    while(fscanf(in,"%s %d %s\n",id1, &wt, id2) == 3){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        GRAPHinsertE(G,i,j, wt);
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
    g->madj[v][w] = e.wt;
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

int isregular(Graph G){
    int i, j, *indegree, *outdegree;
    indegree = calloc(G->V, sizeof(int));
    outdegree = calloc(G->V, sizeof(int));
    for(i=0; i<G->V; i++)
        for(j=0; j<G->V; j++)
            if(G->madj[i][j]){
                indegree[j]++;
                outdegree[i]++;
            }
    for(i=1; i<G->V; i++){
        if(indegree[i] != outdegree[i] || indegree[i] != indegree[0])
            return 0;
    }
    return 1;
}

static void AllPathR(Graph G, int src, Edge *sol, Edge *bestsol, int *visited, int curLen, int *bestlen, int *bestwt, int curwt){
    int i, terminal = 1;
    visited[src] = 1;
    for(i=0; i<G->V; i++)
        if(G->madj[src][i] != 0)
            if(visited[i] == 0) {
                sol[curLen] = EdgeCreate(src, i, G->madj[src][i]);
                AllPathR(G, i, sol, bestsol, visited, curLen+1, bestlen, bestwt, curwt+G->madj[src][i]);
                terminal = 0;
            }
    if(terminal){
        if(*bestwt < curwt || *bestlen == -1){
            *bestwt = curwt;
            *bestlen = curLen;
            for(i=0; i<curLen; i++)
                bestsol[i] = sol[i];
        }
    }
    visited[src] = 0;
}

void GRAPHMaximumSimplePath(Graph G, char *id){
    int *visited, src, i, bestLen=0, bestWt = 0;
    Edge *bestsol, *sol;
    bestsol = malloc(G->E* sizeof(int));
    sol = malloc(G->E* sizeof(int));
    visited = calloc(G->V, sizeof(int));
    src = STsearchbyname(G->table, id);
    AllPathR(G, src, sol, bestsol, visited, 0, &bestLen, &bestWt, 0);
    printf("Peso: %d\n", bestWt);
    for(i=0; i<bestLen; i++){
        printf("%s -%d-> %s\n", STgetbyindex(G->table, bestsol[i].v), bestsol[i].wt, STgetbyindex(G->table, bestsol[i].wt));
    }
    free(sol);
    free(bestsol);
}