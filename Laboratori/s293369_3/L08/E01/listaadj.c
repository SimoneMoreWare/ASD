//
// Created by simone on 25/11/22.
//



#include "listadj.h"

typedef struct node *link;
struct node { int v; int wt; link next; };
struct lisadj{int V; int E; link *ladj; ST tabL; link z;} ;
static link NEW(int v,int wt,link next);
static Edgelist EDGElistcreate(int v,int w,int wt);
static void insertL(Listaadj L, Edgelist e);

static link NEW(int v,int wt,link next){
    link x=malloc(sizeof *x);
    if(x==NULL) return NULL;
    x->v=v;
    x->wt=wt;
    x->next=next;
    return x;
}

static Edgelist EDGElistcreate(int v,int w,int wt){
    Edgelist e;
    e.v=v;
    e.w=w;
    e.wt=wt;
    return e;
}

Listaadj LISTinit(int V){
    int v;
    Listaadj L = malloc(sizeof *L);
    if (L == NULL)
        return NULL;

    L->V = V;
    L->E = 0;
    L->z = NEW(-1, 0, NULL);
    if (L->z == NULL)
        return NULL;
    L->ladj = malloc(L->V*sizeof(link));
    if (L->ladj == NULL)
        return NULL;
    for (v = 0; v < L->V; v++)
        L->ladj[v] = L->z;
    L->tabL = STinit(V);
    if (L->tabL == NULL)
        return NULL;
    return L;
}

void LISTfree(Listaadj L){
    int v;
    link t,next;
    for(v=0;v< STsize(L->tabL);v++){
        for(t=L->ladj[v];t!=L->z;t=next){
            next=t->next;
            if(t!=NULL) free(t);
        }
    }
    STfree(L->tabL);
    free(L->ladj);
    free(L->z);
    free(L);
}

void LISTedges(Listaadj L, Edgelist *a){
    int v,E=0;
    link t;
    for(v=0;v< STsize(L->tabL);v++){
        for(t=L->ladj[v];t!=L->z;t=t->next){
            a[E++]= EDGElistcreate(v,t->v,t->wt);
        }
    }
}

void  LISTinsertL(Listaadj L, int id1, int id2, int wt){
    insertL(L,EDGElistcreate(id1,id2,wt));
}
static void insertL(Listaadj L, Edgelist e) {
    int v = e.v, w = e.w, wt = e.wt;
    L->ladj[v] = NEW(w, wt, L->ladj[v]);
    //L->ladj[w] = NEW(v, wt, L->ladj[w]);
    L->E++;
}

void LISTstore(Listaadj L, FILE *fout) {
    int i;
    Edgelist *a;

    a = malloc(STsize(L->tabL) * sizeof(Edgelist));
    if (a == NULL)
        return;

    LISTedges(L, a);

    fprintf(fout, "vertici: %d\n", L->V);
    fprintf(fout, "archi: %d\n", (L->E)/2);
    for (i = 0; i < STsize(L->tabL); i++ )
        fprintf(fout, "%s\n", STsearchByIndexName(L->tabL, i));


    for (i = 0; i < (L->E); i++)
        fprintf(fout, "%s  %s %d\n", STsearchByIndexName(L->tabL, a[i].v), STsearchByIndexName(L->tabL, a[i].w), a[i].wt);
    free(a);

}

void STinsertWrapper(Listaadj L,char *name, char *subnet){
    STinsert(L->tabL,name,subnet);
}

void check_sottografocompleto_list(Listaadj L){
    char vertice1[MAXCL],vertice2[MAXCL],vertice3[MAXCL];
    int id1,id2,id3;
    int countad=0;
    link t;

    printf("Inserisci i nomi dei tre vertici da vertificare: \n");
    scanf("%s %s %s",vertice1,vertice2,vertice3);

    id1= stgetindex(L->tabL,vertice1);
    id2= stgetindex(L->tabL,vertice2);
    id3= stgetindex(L->tabL,vertice3);int i;

    for(t=L->ladj[id1];t!=L->z;t=t->next) if(t->v==id2) countad++;

    for(t=L->ladj[id2];t!=L->z;t=t->next) if(t->v==id3) countad++;

    for(t=L->ladj[id3];t!=L->z;t=t->next) if(t->v==id1) countad++;

    if(countad==3) printf("I vertici sono adiacenti \n");
    else printf("i vertici non sono adiacneti");

}
