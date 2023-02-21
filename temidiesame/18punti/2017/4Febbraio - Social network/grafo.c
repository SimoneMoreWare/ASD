/*   grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:29
*/
#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "st.h"


typedef struct node *link;
struct node{int id; link next;};
struct grafo{
    int V,E;
    int **madj;
    link *ladj;
    int ladjgen;
    ST table;
    link *cricche;
    int numcricche;
};

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
    g->ladjgen = 0;
    g->madj = malloc(V* sizeof(int*));
    for(i=0; i<V; i++)
        g->madj[i] = calloc(V, sizeof(int));
    g->cricche = malloc(g->V* sizeof(link));
    for(i=0; i<g->V; i++)
        g->cricche[i] = NULL;
    g->numcricche = 0;
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

static link NEW(int id, link next){
    link t;
    t = malloc(sizeof(*t));
    t->id = id;
    t->next = next;
    return t;
}
static Edge EdgeCreate(int v, int w, int wt){
    Edge e;
    e.v = v;
    e.w = w;
    e.wt =wt;
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
    char id1[21], id2[21];
    Graph G;
    ST st = STinit(16);
    while(fscanf(in, "%s %s %d\n", id1, id2, &wt) == 3){
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
    while(fscanf(in, "%s %s %d", id1, id2, &wt) == 3){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        GRAPHinsertE(G, i, j, wt);
    }
    G->table = st;
    return G;
}


Graph GRAPHreadFile(FILE *in){
    return readFile(in);
}

static link LISTinsert(link head, int dato){
    if(head == NULL)
        return NEW(dato, NULL);
    return NEW(dato, head);
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
    g->madj[w][v] = e.wt;
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

char *GRAPHVertexname(Graph G, int i){
    return STgetbyindex(G->table, i);
}

int GRAPHgetbyName(Graph G, char *id){
    return STsearchbyname(G->table, id);
}

int checkCricca(Graph G, int *sol, int dim){
    return 1;
}

void generaR(Graph G, int pos, int *sol, int *bestsol, int *bestwt, int start, int n, int k, int *bestdim){
    int i, j, tmpval;
    if(pos >= k){
        if(checkCricca(G, sol, k)){
            j = G->numcricche++;
            for(i=0; i<k; i++){
                G->cricche[j] = LISTinsert(G->cricche[j], sol[i]);
            }

        }
        return;
    }
    for(i=start; i<n; i++){
        sol[pos] = i;
        generaR(G, pos+1, sol, bestsol, bestwt, i+1, n, k, bestdim);
    }
}


void generaCricche(Graph G){
    int *sol, *bestsol, bestwt = 0, bestdim = 1,i;
    sol = malloc(G->V* sizeof(int));
    bestsol = malloc(G->V* sizeof(int));
    for(i = 1; i<G->V; i++){
        generaR(G, 0, sol, bestsol, &bestwt, 0, G->V, i, &bestdim);
    }
    printf("Cricca massimale:\n");
    for(i=0; i<bestdim; i++){
        printf("%s ", STgetbyindex(G->table,bestsol[i]));
    }
    free(sol);
    free(bestsol);
}