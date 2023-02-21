/*   grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:42:00
*/
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "st.h"


typedef struct node *link;
struct node{int id; link next;};
struct grafo{int V,E; int **madj; link *ladj;int ladjgen; ST table; int *sourcenode;};

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
    g->ladjgen = 0;
    g->madj = malloc(V* sizeof(int*));
    for(i=0; i<V; i++)
        g->madj[i] = calloc(V, sizeof(int));
    g->sourcenode = calloc(V, sizeof(int));
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
    Graph G;
    ST st = STinit(16);
    while(fscanf(in, "%s %s\n", id1, id2) == 2){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        if(i == -1)
            STinsert(st, id1);
        if(j == -1)
            STinsert(st, id2);
    }
    STprint(st);
    rewind(in);
    n = getN(st);
    G = GRAPHinit(n);
    while(fscanf(in, "%s %s", id1, id2) == 2){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        GRAPHinsertE(G, i, j);
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
            printf("%d ",G->madj[i][j]);
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

int *leggiRegali(FILE *in, Graph G){
    int *regali,n,i,k,j;
    char id[16];
    regali = malloc(G->V* sizeof(int));
    fscanf(in, "%d", &n);
    for(i=0; i<n; i++){
        fscanf(in,"%d", &k);
        for(j=0; j<k; j++) {
            fscanf(in, "%s", id);
            regali[STsearchbyname(G->table, id)] = i;
        }
    }
    return regali;
}

int checkRegali(Graph G, int *regali){
    int i,j, flag = 1;
    for(i=0; i<G->V; i++){
        for(j=0; j<G->V; j++){
            if(G->madj[i][j] == 1){
                if(regali[i] == regali[j])
                    return 0;
            }
        }
    }
    return flag;
}

int GRAPHmaximumDegree(Graph G){
    int i,j, sum, max = 0;
    for(i=0; i<G->V; i++){
        sum = 0;
        for(j=0; j<G->V; j++){
            if(G->madj[i][j] == 1)
                sum++;
        }
        if(sum > max)
            max = sum;
    }
    return max;
}

char *GRAPHVertexname(Graph G, int i){
    return STgetbyindex(G->table, i);
}