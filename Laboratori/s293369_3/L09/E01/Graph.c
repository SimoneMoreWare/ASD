#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define maxWT INT_MAX
#define MAXC 10

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;

    G->V = V;
    G->E = 0;
    G->z = NEW(-1, 0, NULL);
    if (G->z == NULL)
        return NULL;
    G->ladj = malloc(G->V*sizeof(link));
    if (G->ladj == NULL)
        return NULL;
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = next) {
            next = t->next;
            free(t);
        }
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    if (G == NULL)
        return NULL;

    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i);
    }

    while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            a[E++] = EDGEcreate(v, t->v, t->wt);
}

void GRAPHstore(Graph G, FILE *fout) {
    int i;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL) return;

    GRAPHedges(G, a);

    for (i = 0; i < G->E; i++) fprintf(fout, "(%s, %s) | Peso: %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

}

int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

static void  removeE(Graph G, Edge e) {
    int v = e.v, w = e.w;
    link x;
    if (G->ladj[v]->v == w) {
        G->ladj[v] = G->ladj[v]->next;
        G->E--;
    }
    else
        for (x = G->ladj[v]; x != G->z; x = x->next)
            if (x->next->v == w) {
                x->next = x->next->next;
                G->E--;
            }
}

void GRAPHspBF(Graph G, int id){
    int v, w, negcycfound;
    link t;
    int *st, *mindist;

    st = malloc(G->V*sizeof(int));
    mindist = malloc(G->V*sizeof(int));
    if ((st == NULL) || (mindist == NULL))
        return;

    for ( v = 0; v < G->V; v++) {
        st[v]= -1;
        mindist[v] = maxWT;
    }

    mindist[id] = 0;
    st[id] = id;

    for (w = 0; w < G->V - 1; w++)
        for (v = 0; v < G->V; v++)
            if (mindist[v] < maxWT)
                for (t = G->ladj[v]; t != G->z ; t = t->next)
                    if (mindist[t->v] > mindist[v] + t->wt) {
                        mindist[t->v] = mindist[v] + t->wt;
                        st[t->v] = v;
                    }
    negcycfound = 0;
    for (v = 0; v < G->V; v++)
        if (mindist[v] < maxWT)
            for (t = G->ladj[v]; t != G->z ; t = t->next)
                if (mindist[t->v] > mindist[v] + t->wt)
                    negcycfound = 1;
    if (negcycfound == 0) {
        printf("\n Shortest path tree\n");
        for (v = 0; v < G->V; v++)
            printf("Parent of %s is %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));

        printf("\n Minimum distances from node %s\n", STsearchByIndex(G->tab, id));
        for (v = 0; v < G->V; v++)
            printf("mindist[%s] = %d \n", STsearchByIndex(G->tab, v), mindist[v]);
    }
    else
        printf("\n Negative cycle found!\n");
}

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int **flag_back) {
    link t; int v, w = e.w; Edge x;
    //if (e.v != e.w) printf("edge (%s, %s) is tree \n", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w)) ;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v,t->wt), time, pre, post, st,&(*flag_back));
        else {
            v = t->v;
            x = EDGEcreate(w, v,t->wt);
            if (post[v] == -1){
                **flag_back=1;
                printf("(%s, %s) | Peso: %d\n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w),t->wt);
            }
            /*else
            if(pre[v]>pre[w])
                printf("edge (%s, %s) is forward \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
            else
                printf("edge (%s, %s) is cross \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));*/
        }
    post[w] = (*time)++;
}

void GRAPHdfs(Graph G, int id,int *flag_back) {
    int v, time=0, *pre, *post, *st;
    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));

    if ((pre == NULL) || (post == NULL) || (st == NULL)) return;

    for (v=0; v < G->V; v++) {
        pre[v] = -1;
        post[v] = -1;
        st[v] =  -1;
    }

    dfsR(G, EDGEcreate(id,id,0), &time, pre, post, st,&flag_back);

    for (v=0; v < G->V; v++)
        if (pre[v]== -1)
            dfsR(G, EDGEcreate(v,v,0), &time, pre, post, st,&flag_back);

    /*printf("discovery/endprocessing time labels \n");
    for (v=0; v < G->V; v++)
        printf("vertex %s : %d/%d \n", STsearchByIndex(G->tab, v), pre[v], post[v]);

    printf("resulting DFS tree \n");
    for (v=0; v < G->V; v++)
        printf("parent of vertex %s is vertex  %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));*/
}

int GRAPHfvertexdim(Graph G){
    return STsize(G->tab);
}

