
#include "GRAPH.h"
#include "SymbolTable.h"


struct grafo_t {
    int V, E;
    int **matrixadj;
    ST st;
};

static int **matrixadj(int nr, int nc, int val) {
    int **matrix;
    int i,j;
    matrix = malloc(nr *sizeof(int *));
    for(i=0;i<nr;i++)
        matrix[i] = malloc(nc *sizeof(int));
    for(i=0;i<nr;i++)
        for(j=0;j<nc;j++)
            matrix[i][j] = val;
    return matrix;
}




GRAPH GRAPHinit() {
    GRAPH G = malloc(sizeof(*G));
    if (G==NULL) {
        printf("ERRORE!!\n");
        exit(-1);
    }
    G->V = 0;
    G->E = 0;
    G->st = STinit(1);
    G->matrixadj = NULL;
    return G;
}




static Edge EDGecreate(int v1, int v2) {
    Edge e;
    e.v1 = v1;
    e.v2 = v2;
    return e;
}




void GRAPHinsertEdge(GRAPH G, Edge e) {
    int v1 = e.v1;
    int v2 = e.v2;
    if (G->matrixadj[v1][v2]==0)
        G->E++;
    G->matrixadj[v1][v2] = 1;
    return;
}




GRAPH GRAPHload(char *nomefile, int *nv) {
    GRAPH G = GRAPHinit();
    int id1, id2;
    char label1[MAX];
    char label2[MAX];
    item it1, it2;
    FILE *fp;

    fp = fopen(nomefile, "r");
    if (fp==NULL) {
        printf("Errore\n");
        exit(-1);
    }

    while (fscanf(fp, "%s %s\n", label1, label2)==2) {
        id1 = STsearchbyname(G->st, label1);
        if (id1==-1) {
            G->V++;
            it1 = ITEMcrea(label1);
            STinsert(G->st, it1);
        }
        id2 = STsearchbyname(G->st, label2);
        if (id2==-1) {
            G->V++;
            it2 = ITEMcrea(label2);
            STinsert(G->st, it2);
        }
    }
    G->matrixadj = matrixadj(G->V, G->V, 0);
    rewind(fp);
    while (fscanf(fp, "%s %s", label1, label2)==2) {
        id1 = STsearchbyname(G->st, label1);
        id2 = STsearchbyname(G->st, label2);
        if (id1>=0 && id2>=0) {
            GRAPHinsertEdge(G, EDGecreate(id1, id2));
        }
    }

    return G;
}




boolean IsKernel(char *nomefile, GRAPH G) {
    FILE *fp;
    int idV;
    int *kernel;
    int *vertici;
    int index =0, i, j, cnt=0;
    char label[MAX];

    fp = fopen(nomefile, "r");
    if (fp==NULL) {
        printf("ERRORE\n");
        exit(-1);
    }

    kernel=(int*)malloc(G->V*sizeof(int));
    while (fscanf(fp, "%s", label)==1) {
        idV = STsearchbyname(G->st, label);
        if (idV>=0) {
            for(i=0; i<index; i++){
                if(G->matrixadj[kernel[i]][idV]==1)
                    return FALSO;
                if(G->matrixadj[idV][kernel[i]]==1)
                    return FALSO;
            }
        }
        kernel[index++]=idV;
    }
    vertici = calloc(G->V , sizeof(int));

    for(i=0;i<index;i++) {
        for(j=0;j<G->V;j++) {
           if(kernel[i]!=j && G->matrixadj[kernel[i]][j]==1)
                vertici[j]++;
        }
    }

    for(i=0;i<G->V;i++) {
       if(vertici[i]>0)
            cnt++;
    }
    if(cnt!=(G->V)-index)
        return FALSO;
    return VERO;
}




static boolean powersetR(int pos, GRAPH g, int *sol, int k, int start) {
    int i;
    if (pos>=k) {
        if(IsValid(g, sol, pos)==VERO)
            return VERO;
        return FALSO;
    }
    for(i=start;i<g->V;i++) {
        sol[pos] = i;
        if (powersetR(pos+1, g, sol, k, i+1)==VERO)
            return VERO;

    }
    return FALSO;

}




kernel powerset(GRAPH G) {
    kernel k;
    int i,j;
    int *sol;
    item it;
    sol = malloc(G->V *sizeof(int));

    for(i=2;i<G->V;i++) {
        if (powersetR(0, G, sol, i, 0)==VERO) {
           break;
        }

    }
    k.size = i;
    k.kernel = malloc(k.size *sizeof(int));
    for(j=0;j<k.size;j++) {
        k.kernel[j] = sol[j];
    }

    printf("\nKernel a cardinalita' minima:\n");
    for(j=0;j<k.size;j++) {
       it=STsearchbyIndex(G->st, k.kernel[j]);
       printf("%s ", it.nome);
    }
    printf("\n");
    return k;

}




boolean IsValid(GRAPH G, int *kernel, int dim) {
    int *vertici;
    int i, j, cnt=0;


    for(i=0; i<dim; i++){
        for(j=0; j<dim; j++){
            if(kernel[i]!=kernel[j] && G->matrixadj[kernel[i]][kernel[j]]==1)
                return FALSO;
            if(kernel[i]!=kernel[j] && G->matrixadj[kernel[j]][kernel[i]]==1)
                return FALSO;
        }
    }
    vertici = calloc(G->V , sizeof(int));

    for(i=0;i<dim;i++) {
        for(j=0;j<G->V;j++) {
           if(kernel[i]!=j && G->matrixadj[kernel[i]][j]==1)
                vertici[j]++;
        }
    }

    for(i=0;i<G->V;i++) {
       if(vertici[i]>0)
            cnt++;
    }
    if(cnt!=(G->V)-dim)
        return FALSO;
    return VERO;
}




static void pathR(GRAPH g, kernel k, int *max, int cnt, int v, int w, int *visited){
    int t;
    if(v==w){
        if(cnt>*(max)){
            *(max)=cnt;
        }
        return;
    }

    if(isVertexKernel(v, k)==VERO)
        cnt++;
    visited[v]=1;
    for(t=0; t<g->V; t++){
        if(g->matrixadj[v][t]==1){
            if(visited[t]==0){
              pathR(g, k, max, cnt, t, w, visited);
            }
        }
    }
    visited[v]=0;
    return;
}




void GRAPHpath(GRAPH g, kernel k){
    int max=0, cnt=0, v, w;
    int *visited;

    visited=(int*)calloc(g->V, sizeof(int));
    if(visited==NULL){
        printf("Errore nell'allocazione.");
        exit(EXIT_FAILURE);
    }

    for(v=0; v<g->V; v++){
        for(w=0; w<g->V; w++){
            pathR(g, k, &max, cnt, v, w, visited);
        }
    }

    printf("\nIl cammino semplice che attraversa il maggior numero di nodi del kernel passa per %d nodi del kernel.\n", max);
    return;
}




boolean isVertexKernel(int v, kernel k){
    int i;
    for(i=0; i<k.size; i++){
        if(v==k.kernel[i]){
            return VERO;
        }
    }
    return FALSO;
}




static void malloc2D(int **matrix, int nr) {
    int i;
    if(matrix!=NULL){
        for(i=0;i<nr;i++)
            free(matrix[i]);
        free(matrix);
    }
    return;
}




void GRAPHfree(GRAPH g){
    if(g!=NULL){
        STfree(g->st);
        malloc2D(g->matrixadj, g->V);
        free(g);
    }
    return;
}
