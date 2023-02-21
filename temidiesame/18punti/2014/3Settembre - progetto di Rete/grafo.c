/*   grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 21/12/2020, 18:27:25
*/
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "st.h"
#include "queue.h"



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
    int i,n;
    char id[30];
    ST st;
    Graph G;
    st = STinit(16);
    while(fscanf(in, "%s", id) == 1){
        i = STsearchbyname(st, id);
        if(i == -1)
            STinsert(st, id);
    }
    n = STgetN(st);
    G = GRAPHinit(n);
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
    STprint(G->table);
    for(i=0; i<G->V; i++){
        for(j=0; j <G->V; j++)
            printf("%3d ",G->madj[i][j]);
        printf("\n");
    }
}

static int generaArchi(int pos, int sol[2], Edge *v, Graph G, int dim, int start){
    int i;
    if(pos >= 2){
        v[dim] = EdgeCreate(sol[0], sol[1]);
        return dim+1;
    }
    for(i=start; i<G->V; i++){
        sol[pos] = i;
        dim = generaArchi(pos+1, sol, v, G, dim, i+1);
    }
    return dim;
}

int GRAPHedges(Graph G, Edge *v){
    int dim, sol[2];
    dim = generaArchi(0, sol, v, G, 0, 0);
    return dim;
}

char *GRAPHvertexbyindex(Graph G, int index){
    return STgetbyindex(G->table, index);
}

static void dfsR(Graph G, int *visited, Edge E){
    int i;
    visited[E.w] = 1;
    for(i = 0; i<G->V; i++)
        if(G->madj[E.w][i] == 1)
            if(!visited[i])
                dfsR(G, visited, EdgeCreate(E.w, i));
}

int bfs(Graph G, Edge e, int *time, int *pre, int *dist){
    int v, maxdist=0;
    Q q = QUEUEinit(G->V);
    QUEUEput(q,e);
    while(!QUEUEempty(q)){
        if(pre[( e=QUEUEget(q)).w] == -1){
            pre[e.w] = (*time)++;
            dist[e.w] = dist[e.v]+1;
            if(dist[e.w] > maxdist)
                maxdist = dist[e.w];
            for(v=0; v<G->V; v++)
                if(G->madj[e.w][v]!=0)
                    if(pre[v] == -1)
                        QUEUEput(q,EdgeCreate(e.w,v));
        }
    }
    return maxdist;
}

int getDiameter(Graph G, int id){
    int v, time=0, *pre, *dist, max;
    pre = malloc(G->V* sizeof(int));
    dist = malloc(G->V* sizeof(int));
    for(v=0; v<G->V; v++){
        pre[v] = -1;
        dist[v] = -1;
    }
    max = bfs(G, EdgeCreate(id,id), &time, pre, dist);
    return max;
}

static int isConnected(Graph G, Edge *sol, int dim){
    int i, *visited, isconnect=1;
    visited = malloc(G->V* sizeof(int));
    for(i=0; i<G->V; i++)
        visited[i] = 0;
    for(i=0; i<dim; i++)
        GRAPHinsertE(G, sol[i].v, sol[i].w);
    dfsR(G, visited, EdgeCreate(0, 0));
    for(i=0; i<G->V; i++)
        if(visited[i] == 0)
            isconnect = 0;
    for(i=0; i<dim; i++){
        GRAPHremoveE(G, sol[i].v, sol[i].w);
    }
    free(visited);
    return isconnect ;
}

static int checkDegree(Graph G, Edge *sol, int dim, int m){
    int i,j, *degree, flag = 1;
    degree = malloc(G->V* sizeof(int));
    for(i=0; i<G->V; i++)
        degree[i] = 0;
    for(i=0; i<dim; i++)
        GRAPHinsertE(G, sol[i].v, sol[i].w);
    for(i=0; i<G->V; i++)
        for(j=0; j<G->V; j++)
            if(G->madj[i][j])
                degree[i]++;
    for(i=0; i<G->V; i++)
        if(degree[i] > m)
            flag = 0;
    for(i=0; i<dim; i++){
        GRAPHremoveE(G, sol[i].v, sol[i].w);
    }
    return flag;
}

static int checkDistance(Graph G, Edge *sol, int dim, int k){
    int i, flag = 1;
    for(i=0; i<dim; i++)
        GRAPHinsertE(G, sol[i].v, sol[i].w);
    if(k < getDiameter(G, 0))
        flag = 0;
    for(i=0; i<dim; i++){
        GRAPHremoveE(G, sol[i].v, sol[i].w);
    }
    return flag;
}

static int combinazioni(Graph G, int pos, Edge *sol, Edge *val, int dim, int l, int start){
    int i;
    if(pos >=l){
        if(isConnected(G, sol, l) && checkDegree(G, sol, l, 2) && checkDistance(G, sol, l, 2)){
            return 1;
        }
        return 0;
    }
    for(i=start; i<dim; i++){
        sol[pos] = val[i];
        if(combinazioni(G, pos+1, sol, val, dim, l, i+1))
            return 1;
    }
    return 0;
}

void GRAPHconnect(Graph G,Edge *val, int dim){
    Edge *sol;
    sol = malloc(dim* sizeof(Edge));
    int i, l=0,trovata = 0;
    for(i=1; i<dim && trovata == 0; i++){
        if(combinazioni(G, 0, sol, val, dim, i, 0)) {
            trovata = 1;
            l = i;
        }
    }
    if(trovata) {
        printf("Insieme minimo: %d archi\n", l);
        for (i = 0; i < l; i++)
            printf("%s -> %s\n", STgetbyindex(G->table, sol[i].v), STgetbyindex(G->table, sol[i].w));
    }
}

