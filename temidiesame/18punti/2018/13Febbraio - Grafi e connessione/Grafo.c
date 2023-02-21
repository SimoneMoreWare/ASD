/*   Grafo.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:57
*/
#include "Grafo.h"
#include "st.h"

#include "stdio.h"
#include "stdlib.h"
#include "queue.h"

typedef struct node *link;
struct node{int id; int wt; link next;};
struct grafo{int V,E; float **madj; link *ladj;int ladjgen; ST table; int *sourcenode;};

static link NEW(int dst, int w, link next);
static Edge EdgeCreate(int v, int w, float wt);
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
    g->madj = malloc(V* sizeof(float*));
    for(i=0; i<V; i++)
        g->madj[i] = calloc(V, sizeof(float));
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

static Edge EdgeCreate(int v, int w, float wt){
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
    float x,y;
    char nome[31],id1[30], id2[30];
    fscanf(in, "%d\n",&n);
    Graph G = GRAPHinit(n);
    ST st;
    st = STinit(n);
    for(i=0; i<n; i++){
        fscanf(in,"%s %f %f\n", nome, &x, &y);
        STinsert(st, pointCreate(nome, x, y ));
    }
    while(fscanf(in,"%s %s\n",id1,id2) == 2){
        i = STsearchbyname(st, id1);
        j = STsearchbyname(st, id2);
        wt = distance(STgetbyindex(st,i),STgetbyindex(st,j));
        GRAPHinsertE(G,i,j,wt);
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

void dfsR(Graph G, Edge e, int *time, int *pre, int *flag){
    link t;
    int v, w= e.w;
    if(e.v != e.w)
        printf("");
    pre[w] = (*time)++;
    for(t = G->ladj[w]; t != NULL; t=t->next)
        if(pre[t->id] == -1)
            dfsR(G,EdgeCreate(w,t->id,1), time, pre, flag);
        else{
            v = t->id;
            if(pre[w] < pre[v])
                *flag = 0;
        }
}

static int isAciclico(Graph G){
    int isAciclico = 1, v, time=0, *pre;
    pre = malloc(G->V * sizeof(int));
    for(v=0; v < G->V; v++)
        pre[v] = -1;
    for(v=0; v<G->V; v++)
        if(pre[v] == -1)
            dfsR(G,EdgeCreate(v,v,1), &time, pre, &isAciclico);
    return isAciclico;
}

static int checkSum(Edge *sol, int l){
    int i, sum=0;
    for(i=0; i<l; i++){
        sum += sol[i].wt;
    }
    return sum;
}

static void combinazioni(Graph G,int pos, Edge *sol, Edge *bestsol, Edge *archi,  int *bestval, int l, int start, int *trovata){
    int i, tmpval;
    if(pos >= l){
        for(i=0; i<l; i++){
            insertE(G,sol[i]);
        }
        if(isConnesso(G)){
            *trovata = 1;
            tmpval = getDiameter(G, 0);
            if(tmpval < *bestval) {
                for (i = 0; i < l; i++)
                    bestsol[i] = sol[i];
                *bestval = tmpval;
            }
        }
        for(i=0; i<l; i++){
            removeE(G,sol[i]);
        }
        return;
    }
    for(i = start; i<G->E; i++){
        sol[pos] = archi[i];
        combinazioni(G, pos+1, sol, bestsol, archi, bestval, l, i+1, trovata);
    }
    return;
}

static Edge *createEdgelist(Graph G, int *n){
    Edge *archi;
    int i,j,k=0;
    archi = malloc(G->V*G->V* sizeof(Edge));
    for(i=0; i<G->V; i++)
        for(j=0; j<G->V; j++)
            if(G->madj[i][j] == 0)
                archi[k++] = EdgeCreate(i, j, distance(STgetbyindex(G->table,i),STgetbyindex(G->table,j)));
    *n = k;
    return archi;
}

int bfs(Graph G, Edge e, int *time, int *pre, int *dist){
    int v, maxdist=0;
    Q q = QUEUEinit();
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
                        QUEUEput(q,EdgeCreate(e.w,v,G->madj[e.w][v]));
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
    max = bfs(G, EdgeCreate(id,id,0), &time, pre, dist);
    return max;
}

void GRAPHconnect(Graph G){
    Edge *e;
    int n = 0;
    e = createEdgelist(G, &n);

}