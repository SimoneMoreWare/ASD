//
// Created by simone on 25/11/22.
//

#include <stdlib.h>
//#include <limits.h>
#include "Graph.h"

#define MAXC 51
#define maxWT 0
struct graph {int V; int E; int **madj; ST tab; };
static Edge  EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static int graph_get_index(Graph G, char *name, char *subnet);

static int graph_get_index(Graph G, char *name, char *subnet) {
    int id;
    id = stgetindex(G->tab, name);

    if (id == -1) {
        id = STinsert(G->tab, name, subnet);
    }
    return id;
}

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    if (t==NULL)
        return NULL;

    for (i=0; i < r; i++) {
        t[i] = malloc(c * sizeof(int));
        if (t[i]==NULL)
            return NULL;
    }
    for (i=0; i < r; i++)
        for (j=0; j < c; j++)
            t[i][j] = val;
    return t;
}


Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, maxWT);
    if (G->madj == NULL)
        return NULL;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    if(G==NULL) return;
    for (i=0; i<G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G);
}

int EDGEreadfromfile(FILE *fin){
    int count = 1;
    char c;
    for (c = getc(fin); c != EOF; c = getc(fin)) if (c == '\n') count = count + 1;
    return count;
}

Graph GRAPHload(FILE *fin){
    int E,i,wt;
    char lab1[MAXC],rete1[MAXC],lab2[MAXC],rete2[MAXC];
    Graph G;
    E=EDGEreadfromfile(fin);
    printf("%d archi: ",E);
    rewind(fin);
    G= GRAPHinit(2*E);
    for(i=0;i<E;i++){
        fscanf(fin,"%s %s %s %s %d\n",lab1,rete1,lab2,rete2,&wt);
        GRAPHinsertE(G,graph_get_index(G,lab1,rete1), graph_get_index(G,lab2,rete2),wt);
    }
    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == maxWT) G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void  GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v=0; v < G->V; v++)
        for (w=v+1; w < G->V; w++)
            if (G->madj[v][w] != maxWT)
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

void GRAPHstore(Graph G,FILE *fout){
    int i;
    Edge *a;

    a=malloc(G->E * sizeof(Edge));
    if(a==NULL) return;

    GRAPHedges(G,a);

    fprintf(fout,"%d\n",G->E);

    for(i=0;i<G->E;i++) fprintf(fout,"%s %s %s %s %d\n", STsearchByIndexName(G->tab,a[i].v), STsearchByIndexSubnet(G->tab,a[i].v),STsearchByIndexName(G->tab,a[i].w),
                                STsearchByIndexSubnet(G->tab,a[i].w),a[i].wt);
    free(a);
}

Listaadj LISTload(Graph G){
    Listaadj L=NULL;
    int i,j;
    L=LISTinit((STsize(G->tab)));
    for(i=0;i< STsize(G->tab);i++){
        STinsertWrapper(L,STsearchByIndexName(G->tab,i),STsearchByIndexSubnet(G->tab,i));
    }
    for(i=0;i<STsize(G->tab);i++){
        for(j=0;j< STsize(G->tab);j++){
            if(G->madj[i][j]!=0){
                LISTinsertL(L,i,j,G->madj[i][j]);
                //LISTinsertL(L,j,i,G->madj[i][j]);
            }
        }
    }
    return L;
}

void check_sottografocompleto_matrix(Graph G){
    char vertice1[MAXC],vertice2[MAXC],vertice3[MAXC];
    int id1,id2,id3;
    int countad=0;
    printf("Inserisci i nomi dei tre vertici da vertificare: \n");
    scanf("%s %s %s",vertice1,vertice2,vertice3);
    id1= stgetindex(G->tab,vertice1);
    id2= stgetindex(G->tab,vertice2);
    id3= stgetindex(G->tab,vertice3);
    if(G->madj[id1][id2]==G->madj[id2][id1] && G->madj[id1][id2]!=0 && G->madj[id2][id1]!=0) countad++;
    if(G->madj[id1][id3]==G->madj[id3][id1] && G->madj[id3][id1]!=0 && G->madj[id3][id1]!=0) countad++;
    if(G->madj[id2][id3]==G->madj[id3][id2] && G->madj[id2][id3]!=0 && G->madj[id3][id2]!=0) countad++;
    if(countad==3) printf("I vertici sono adiacenti \n");
    else printf("i vertici non sono adiacneti");
}

void printsortvertex(Graph G){
    int i,j,k, *vect = malloc(STsize(G->tab) * sizeof(int));

    STsort(G->tab,vect);
    for(i=0;i< STsize(G->tab);i++){
        printf("%s\n", STsearchByIndexName(G->tab,vect[i]));
        for(j=0;j< STsize(G->tab);j++){
            if(G->madj[vect[i]][vect[j]]!=0 && i!=j){
                printf(" %s\n ", STsearchByIndexName(G->tab,vect[j]));
            }
        }
        printf("\n----\n");
    }
    free(vect);
}
