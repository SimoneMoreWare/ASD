#include "Graph.h"

typedef struct Graph_t {
    int **madj;
    int V;
} *Graph;

static int **MATRinit(int r, int c, int v) {
    int i, j, **m;
    
    m = (int**) malloc(r*sizeof(int*));
    for (i = 0; i < r; i++) {
        m[i] = (int*) malloc(c*sizeof(int));
        for (j = 0; j < c; j++)
            m[i][j] = v;
    }
    
    return m;
}

int GRAPHfindEdge(Graph G, int v, int w) {
    return G->madj[v][w];
}

int GRAPHvertex(Graph G) {
    return G->V;
}

Graph GRAPHfile(FILE* file) {
    int v, w;
    Graph G;

    G = (Graph) malloc(sizeof(*G));
    fscanf(file, "%d", &(G->V));
    G->madj = MATRinit(G->V, G->V, 0);
    while (fscanf(file, "%d %d", &v, &w) == 2)
        G->madj[v][w] = 1;

    return G;
}


static int checkColl(Graph G, Coll V) {
    if (GRAPHfindEdge(G, V->u, V->v) == 0 || 
        GRAPHfindEdge(G, V->u, V->w) == 0 ||
        GRAPHfindEdge(G, V->v, V->w) == 0)
        return 0;
    
    return 1;
}

int checkTriPack(Graph G, TriPack TP) {
    int i, n, *V;
    Coll tmp;

    n = GRAPHvertex(G);
    V = (int*) malloc(n * sizeof(int));
    for (i = 0; i < n; i++)
        V[i] = -1;

    for (i = 0; i < TP->n; i++) {
        tmp = TP->V[i];
        
        // controlla che siano presenti gli archi nel grafo
        if (checkColl(G, tmp) == 0)
            return 0;
        /* 
            controlla che i vertici non siano stati presi per
            avere sottoinsiemi disgiunti.
        */
        if (V[tmp->u] != -1 || 
            V[tmp->v] != -1 || 
            V[tmp->w] != -1)
            return 0;
        V[tmp->u] = V[tmp->v] = V[tmp->w] = i;
    }

    return 1;
}

int GRAPHcheckFile(FILE* file, Graph G) {
    TriPack TP;
    int check;

    TP = TRIPACKfile(file);
    check = checkTriPack(G, TP);
    TRIPACKfree(TP);
    
    return check;
}

static int comb_sempl(int pos, Graph G, Coll *V, Coll sol, int k, int start, int cnt) {
    int i;

    if (pos >= k) {
        if (checkColl(G, sol) == 1) {
            V[cnt] = COLLcopy(sol);
            cnt++;
        }
        return cnt;
    }

    for (i = start; i < G->V; i++) {
        sol = COLLset(sol, pos, i);
        cnt = comb_sempl(pos+1, G, V, sol, k, start+1, cnt);
    }

    return cnt;
}

static void powerset_r(int pos, Graph G, TriPack sol, Coll *V, int n, int k, TriPack *best_sol, int start) {
    int i;

    if (pos > k) {
        if (checkTriPack(G, sol) == 1)
            if (TRIPACKdim(sol) > TRIPACKdim(*best_sol))
                *best_sol = TRIPACKcopy(sol);
        return;
    }

    for (i = start; i < n; i++) {
        sol->V[pos] = COLLcopy(V[i]);
        sol->n = sol->n + 1;
        powerset_r(pos+1, G, sol, V, n, k, best_sol, start+1);
        sol->n = sol->n - 1;
    }
    return;
}

static void powerset(Graph G, Coll *V, int n, TriPack *best_sol) {
    int i;
    TriPack sol = TRIPACKinit(G->V);

    for (i = 0; i < n; i++)
        powerset_r(0, G, sol, V, n, i, best_sol, 0);
}

void GRAPHfindMaxTripack(Graph G) {
    TriPack best_solTP = TRIPACKinit(G->V);
    int n_max = (G->V*(G->V-1)*(G->V-2))/6;
    Coll *V = (Coll*) malloc(n_max * sizeof(Coll));
    Coll solV = COLLinit(-1, -1, -1);
    int n;

    n = comb_sempl(0, G, V, solV, 3, 0, 0);
    powerset(G, V, n, &best_solTP);

    TRIPACKstore(stdout, best_solTP);
}
