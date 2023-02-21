/*   graph.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:47:31
*/
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "st.h"


struct grafo{int V,E; int **madj; ST table; int *deleted, *degree;};

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
    g->table = STinit(V);
    g->madj = malloc(V* sizeof(int*));
    for(i=0; i<V; i++)
        g->madj[i] = calloc(V, sizeof(int));
    g->degree = malloc(g->V* sizeof(int));
    g->deleted = malloc(g->V* sizeof(int));
    for(i=0; i<V; i++)
        g->deleted[i] = 0;
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

Graph GRAPHload(FILE *in){
    int i,n,j;
    char id1[21], id2[21];
    ST st;
    Graph G;
    fscanf(in, "%d", &n);
    G = GRAPHinit(n);
    for(i=0;i<n; i++) {
        fscanf(in, "%s", id1);
        STinsert(G->table, id1);
    }
    while(fscanf(in, "%s %s\n", id1, id2) == 2){
        i = STsearchbyname(G->table, id1);
        j = STsearchbyname(G->table, id2);
        insertE(G, EdgeCreate(i, j));
    }
    return G;
}

static void removeE(Graph G, Edge e){
    int v = e.v, w = e.w;
    if(G->madj[v][w] != 0){
        G->madj[v][w] = 0;
        G->madj[w][v] = 0;
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

static int calcolagrado(Graph G){
    int i, j, flag =1 ;
    for(i=0; i<G->V; i++) G->degree[i] = 0;
    for(i=0; i<G->V; i++)
        for(j=0; j<G->V; j++)
            if(G->madj[i][j] == 1)
                G->degree[i]++;
    return flag;
}

void generaKcore(Graph G, int k){
    int i, j, flag = 1;
    calcolagrado(G);
    while(flag){
        for(i=0; i<G->V; i++)
            if(G->deleted[i] == 0 && G->degree[i] < k){
                G->deleted[i] = 1;
                for(j=0; j<G->V; j++){
                    if(G->madj[i][j] == 1) {
                        G->madj[i][j] = -1;
                    }
                }
            }
        calcolagrado(G);
        flag = 0;
        for(i=0; i<G->V; i++){
            if(G->deleted[i] == 0 && G->degree[i] < k)
                flag = 1;
        }
    }
    for(i=0; i<G->V; i++){
        if(G->deleted[i] == 0)
            printf("%s\n", STgetbyindex(G->table, i));
    }
}

static Edge *GRAPHEdges(Graph G){
    int i, j, k=0;
    Edge *e = malloc(G->E* sizeof(Edge));
    for(i=0; i<G->V; i++)
        for(j=i; j<G->V; j++)
            if(G->madj[i][j] != 0)
                e[k++] = EdgeCreate(i, j);
    return e;
}

static void dfsR(Graph G, Edge e, int *visited){
    int i;
    visited[e.w] = 1;
    for(i=0; i<G->V; i++){
        if(visited[i]==0 && G->madj[e.w][i]!=0)
            dfsR(G, EdgeCreate(e.w, i), visited);
    }
}

static int is_disconnetted(Graph G, Edge *sol, int j){
    int i, flag = 0, *visited;
    visited = (int*) malloc(G->V* sizeof(int));
    if(visited == NULL)
        return -1;
    for(i=0;i<G->V; i++) visited[i] = 0;
    for(i=0; i<j; i++)
        removeE(G, sol[i]);
    dfsR(G, EdgeCreate(0,0), visited);
    for(i=0; i<G->V; i++){
        if(visited[i] == 0)
            flag = 1;
    }
    for(i=0; i<j; i++)
        insertE(G, sol[i]);
    free(visited);
    return flag;
}

static int combinazioni(Graph G, Edge *sol, int pos, int start, int j, Edge *val){
    int i;
    if(pos == j){
        if(is_disconnetted(G, sol, j))
            return 1;
        else
            return 0;
    }
    for(i=start; i<G->E; i++){
        sol[pos] = val[i];
        if(combinazioni(G, sol, pos+1, i+1, j, val))
            return 1;
    }
    return 0;
}
void checkisjedgeconnected(Graph G, int j){
    int i, flag =1;
    Edge *sol, *val;
    sol = malloc(j*sizeof(Edge));
    val = GRAPHEdges(G);
    for(i=1; i<j && flag==1; i++)
        if(combinazioni(G, sol, 0, 0, i, val))
            flag = 0;
    if(!flag)
        printf("G non j-edge-connected.\n");
    else if(combinazioni(G, sol, 0, 0, j, val))
            for(i=0; i<j; i++)
                printf("%s -> %s\n", STgetbyindex(G->table, sol[i].v),STgetbyindex(G->table, sol[i].w));
    else
        printf("G non e' j-edge-connected.");
}
