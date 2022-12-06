#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

#define MAXC 10

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);

//var globale contatore dagedges

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
    free(a);
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



void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int **flag_back,Edge ***dagedges, int **cnt, int **countedgeback) {
    link t; int v, w = e.w; Edge x;
    //if (e.v != e.w) printf("edge (%s, %s) is tree \n", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w)) ;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v,t->wt), time, pre, post, st,&(*flag_back),dagedges,&(*cnt),&(*countedgeback));
        else {
            v = t->v;
            x = EDGEcreate(w, v,t->wt);
            if (post[v] == -1){
                **flag_back=1;
                (**dagedges)[**cnt].w=x.w;
                (**dagedges)[**cnt].v=x.v;
                (**dagedges)[**cnt].wt=t->wt;
                (**cnt)++;
                (**countedgeback)++;
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

void GRAPHdfs(Graph G, int id,int *flag_back, Edge **dagedges,int *cnt,int *countbackedge) {
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
    *countbackedge=0;
    dfsR(G, EDGEcreate(id,id,0), &time, pre, post, st,&flag_back,&(dagedges),&cnt,&countbackedge);

    for (v=0; v < G->V; v++) if (pre[v]== -1) dfsR(G, EDGEcreate(v,v,0), &time, pre, post, st,&flag_back,&dagedges,&cnt,&countbackedge);

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

void EDGEdag(Graph G,Edge *dagedges,int cnt,int countedgeback){
    int i;
    int j;
    int k=0;
    int massimo=0;
    int sommapeso;
    int rmb;
    for(i=0;i<(cnt/countedgeback);i++){
        sommapeso=0;
        for(j=0;j<countedgeback;j++){
            sommapeso=sommapeso+dagedges[k].wt;
            k++;
        }
        if(sommapeso>massimo){
            massimo=sommapeso;
            rmb=i;
        }
    }
    printf("MAX %d %d %d\n",dagedges[rmb].v,dagedges[rmb].w,dagedges[rmb].wt);

    for(k=0;k<countedgeback;k++) GRAPHremoveE(G,dagedges[rmb+k].v,dagedges[rmb+k].w);
    GRAPHstore(G,stdout);

}

void TSdfsR(Graph D, int v, int *ts, int *pre, int *time) {
    link t; pre[v] = 0;
    for (t = D->ladj[v]; t != D->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(D, t->v, ts, pre, time);
    ts[(*time)--] = v;
}
void DAGrts(Graph D) {
    int v,i, time = (D->V)-1, *pre, *ts;
    pre=malloc((D->V)*sizeof(Graph));
    ts=malloc((D->V)*sizeof(Graph));
    for (v=0; v < D->V; v++) { pre[v] = -1; ts[v] = -1; }
    for (v=0; v < D->V; v++) if (pre[v]== -1) TSdfsR(D, v, ts, pre, &time);
    printf("DAG nodes in topological order \n");
    for (v=0; v<D->V; v++) printf("%s ", STsearchByIndex(D->tab, ts[v]));printf("\n");
    free(pre);
    for(i=0;i<(D->V);i++) DAGlongestpath(D,ts,ts[i],i);
}

void DAGlongestpath(Graph D,int *ts,int id,int i){
    int *d;
    int j;
    int w;
    int v=id;
    link t;
    d=malloc((D->V)*sizeof(int));
    for(j=0;j<(D->V);j++){
        d[j]=-1;
    }
    d[v]=0;
    for(j=i;j<D->V;j++){
        w=ts[j];
        printf("longest %d\n",w);
        if(d[w]==-1) continue;
        for (t = D->ladj[w]; t != D->z; t = t->next){
            printf("Ti prego %d %d | %d\n",w,t->v,t->wt);
            if(d[t->v]==-1 || d[w]+t->wt>d[t->v]){
                d[t->v] = d[w] + t->wt;
                for (v = 0; v < D->V; v++) printf("stima %s: %d\n", STsearchByIndex(D->tab, v), d[v]);
            }
        }
    }

    for (v = 0; v < D->V; v++)
        printf("%s: %d\n", STsearchByIndex(D->tab, v), d[v]);
    printf("\n------\n");
}
