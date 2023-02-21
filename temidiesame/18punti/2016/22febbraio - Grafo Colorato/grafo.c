/*   grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:05
*/
#include "grafo.h"
#include <stdlib.h>
#include "st.h"

typedef struct node *link;
struct node{int id; int wt; link next;};
struct grafo{int V,E; int **madj; link *ladj;int ladjgen; ST table; int *deleted;};

static link NEW(int dst, int w, link next);
static Edge EdgeCreate(int v, int w, int wt);
static void insertE(Graph g, Edge e);
static void removeE(Graph G, Edge e);

static link NEW(int dst, int w, link next){
    link x;
    x = malloc(sizeof(*x));
    x->id = dst;
    x->wt = w;
    x->next =  next;
    return x;
}

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
    g->deleted = calloc(V, sizeof(int));
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
    int i,n,j,wt;
    char id1[30], id2[30], col1[10], col2[10];
    ST st;
    Graph G;
    st = STinit(16);
    while(fscanf(in,"%s %s %d %s %s\n",id1,col1,&wt, id2, col2 ) == 5){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        if(i == -1)
            STinsert(st, ItemCreate(id1,col1));
        if(j == -1)
            STinsert(st, ItemCreate(id2,col2));
        else if(i != -1){
            if(STgetColor(st,i) != (strcmp("ROSSO",col1) ? 'N' : 'R'))
                printf("Inserimento arco %s %s -%d-> %s %s non riuscito causa incongruenza di colore.", id1, col1, wt, id2, col2);
        }
        else if(j != -1){
            if(STgetColor(st,j) != (strcmp("ROSSO",col2) ? 'N' : 'R'))
                printf("Inserimento arco %s %s -%d-> %s %s non riuscito causa incongruenza di colore.", id1, col1, wt, id2, col2);
        }
    }
    n  = getN(st);
    G = GRAPHinit(n);
    G->table = st;
        rewind(in);
    while(fscanf(in,"%s %s %d %s %s\n",id1,col1,&wt, id2, col2 ) == 5){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        GRAPHinsertE(G, i, j, wt);
    }
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
    int v = e.v, w = e.w, wt = e.wt;
    if(g->madj[v][w] == 0)
        g->E++;
    g->madj[v][w] = wt;
}

void GRAPHprintmatrix(Graph G){
    int i,j;
    for(i=0; i<G->V; i++){
        for(j=0; j <G->V; j++)
            printf("%3d ",G->madj[i][j]);
        printf("\n");
    }
}

static link listIns(link head, int dst, int wt){
    head = NEW(dst, wt ,head);
    return head;
}

void GRAPHladjcreate(Graph G){
    int i,j;
    if(G->ladjgen ==0) {
        G->ladjgen = 1;
        G->ladj = malloc(G->V * sizeof(link));
        for (i = 0; i < G->V; i++)
            G->ladj[i] = NULL;
        for (i = 0; i < G->V; i++) {
            for (j = 0; j < G->V; j++) {
                if (G->madj[i][j] != 0) {
                    G->ladj[i] = listIns(G->ladj[i], j, G->madj[i][j]);
                }
            }
        }
    }
}

void GRAPHprintlist(Graph G){
    int i;
    link x;
    if(G->ladjgen == 1) {
        for (i = 0; i < G->V; i++) {
            if (G->ladj[i] != NULL) {
                printf("-%d -> ", i);
                for (x = G->ladj[i]; x->next != NULL; x = x->next) {
                    printf("%d/%d ->", x->id, x->wt);
                }
                printf("%d/%d\n", x->id, x->wt);
            }
        }
    }
    else{
        printf("Lista non ancora generata.\n");
    }
}

static int LISTsearch(link head, int i){
    link x;
    for(x=head; x!=NULL; x=x->next)
        if(x->id == i)
            return 1;
    return 0;
}

int GRAPHedges(Graph G, int *v, int i){
    int j,n=0;
    for(j=0; j<G->V; j++)
        if(G->madj[i][j] != 0)
            v[n++] = j;
    return n;
}

void dfsR(Graph G, Edge e, int *time, int *pre) {
    link t;
    int v, w = e.w;
    if (e.v != e.w)
        printf("");
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != NULL; t = t->next)
        if (pre[t->id] == -1)
            dfsR(G, EdgeCreate(w, t->id, 1), time, pre);
}

static int isConnesso(Graph G){
    int isConnesso = 1, v, time=0, *pre;
    pre = malloc(G->V * sizeof(int));
    for(v=0; v < G->V; v++)
        pre[v] = -1;
    dfsR(G,EdgeCreate(v,v,1), &time, pre);
    for(v=0; v<G->V; v++)
        if(pre[v] == -1)
            isConnesso = 0;
    return isConnesso;
}

static int checkSum(Graph G){
    int i, sum=0;
    link t;
    for(i=0; i<G->V; i++){
        if(G->deleted[i] == 0){
            for(t=G->ladj[i]; t!= NULL; t=t->next)
                if(G->deleted[t->id] == 0)
                    sum += t->wt;
        }
    }
    return sum;
}

static int checkDifference(Graph G){
    int r=0,n=0;
    int i;
    link t;
    for(i=0; i<G->V; i++){
        if(G->deleted[i] == 0){
            if(STgetColor(G->table,i) == 'R')
                r++;
            else
                n++;
        }
    }
    return abs(r-n);
}

static int colorCompatibility(Graph G,int src, int next){
    char c1,c2;
    c1 = STgetColor(G->table,src);
    c2 = STgetColor(G->table, next);
    if(c1 == 'R' && c2 == 'N')
        return 1;
    if(c1 == 'N')
        return 1;
    return 0;
}

static void allPathR(Graph G, int src, Edge *path, Edge *bestpath,int *visited, int curLen, int curW, int *bestLen, int *bestW){
    int i, terminal = 1;
    visited[src] = 1;
    link t;
    for(t = G->ladj[src]; t!= NULL; t=t->next){
        if(!visited[t->id] && colorCompatibility(G, src, t->id)){
            path[curLen] = EdgeCreate(src, t->id, t->wt);
            allPathR(G, t->id, path, bestpath, visited, curLen+1, curW+t->wt, bestLen, bestW);
            terminal = 0;
        }
    }
    if(terminal){
        if(*bestW < curW || *bestLen == -1){
            *bestW = curW;
            *bestLen = curLen;
            for(i=0; i<curLen; i++){
                bestpath[i] = path[i];
            }
        }
    }
    visited[src] = 0;
}

void GRAPHlongestSimplePath(Graph G){
    int i, *visited, len = -1, weigth = 0;
    Edge *path, *bestPath;
    path = malloc(G->E* sizeof(Edge));
    bestPath = malloc(G->E* sizeof(Edge));
    visited = calloc(G->V, sizeof(int));
    allPathR(G, 0, path, bestPath, visited, 0, 0, &len, &weigth);
    printf("Cammino semplice a peso massimo: \n");
    for(i=0; i<len; i++){
        printf("%s -> %s ",STgetbyindex(G->table,bestPath[i].v).id,STgetbyindex(G->table,bestPath[i].w).id);
    }
    free(path);
    free(bestPath);
    free(visited);
}

//TODO combinazioni semplici di vertici a cardinalità crescente