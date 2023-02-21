/*   grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:33
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
    while(fscanf(in,"%s %d %s\n",id1,&wt,id2) == 3){
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

static void AllPathRvw(Graph G, int src, int dest, int *path, int *bestPath, int *visited, int *bestlen, int *bestWt, int curwt, int curlen, int k, int p, int count){
    int i, countk=0;
    visited[src]++;
    path[curlen] = src;
    if(src == dest){
        for(i=0; i<G->V; i++){
            if(visited[i] > 1)
               countk++;
        }
        if(countk < k){
            if(curwt > *bestWt){
                *bestlen = curlen;
                *bestWt = curwt;
                for(i=0; i<curlen; i++)
                    bestPath[i] = path[i];
            }
        }
        return;
    }
    for(i=0; i<G->V; i++){
        if(G->madj[src][i]){
            if(visited[i] && count <= p){
                count++;
                AllPathRvw(G, i, dest, path, bestPath, visited, bestlen, bestWt, curwt+G->madj[src][i], curlen+1, k, p, count);
                visited[i]--;
            }
            else{
                if(!visited[i]){
                    AllPathRvw(G, i, dest, path, bestPath, visited, bestlen, bestWt, curwt+G->madj[src][i], curlen+1, k, p, count);
                    visited[i] = 0;
                }
            }
        }
    }
}


void GRAPHbestPathVW(Graph G, char *id1, char *id2, int k, int p){
    int *path, *bestPath, *visited, bestLen = 0, bestWt = 0, i, v, w;
    path = malloc((G->V+k*p)* sizeof(int));
    bestPath = malloc((G->V+k*p)* sizeof(int));
    visited = malloc(G->V* sizeof(int));
    for(i=0; i<G->V; i++)
        visited[i] = 0;
    v = STsearchbyname(G->table, id1);
    w = STsearchbyname(G->table, id2);
    AllPathRvw(G, v, w, path, bestPath, visited, &bestLen, &bestWt, 0, 0, k, p, 0);
    printf("Cammino ottimo a peso %d\n", bestWt);
    for(i=0; i<bestLen; i++){
        printf("%s ", STgetbyindex(G->table, bestPath[i]));
    }
}
