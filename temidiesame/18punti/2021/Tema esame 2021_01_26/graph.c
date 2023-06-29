#include "graph.h"
#include <math.h>

struct grafo{
	int V, E;
    ST table;
    int **matAdj;
};


//PATH
Path PATHcrea(int nStanze){
	Path p;
    p.stanze=(int*)malloc(nStanze*sizeof(int));
    if(p.stanze==NULL)
        exit(EXIT_FAILURE);
    p.ricchezzaTotale=0;
    p.nStanze=nStanze;
    return p;
}

void PATHprint(Graph g, Path p, FILE *f){
    int i;
    Stanza s;
    fprintf(f, "Ricchezza: %d\n", p.ricchezzaTotale);
    fprintf(f, "Percorso: ");
    for(i=0; i<p.nStanze; i++){
        s=STgetStanza(g->table, p.stanze[i]);
        STANZAprint(s, f);
        fprintf(f, " ");
    }
    return;
}


void PATHclear(Path p){
      if(p.stanze!=NULL)
          free(p.stanze);
      return;
}




//GRAFO
static int **MATRIXinit(int nr, int nc, int value){
    int **m, i, j;

    m=(int**)malloc(nr*sizeof(int*));
    if(m==NULL)
        exit(EXIT_FAILURE);

    for(i=0; i<nr; i++){
        m[i]=(int*)malloc(nc*sizeof(int));
        if(m[i]==NULL)
            exit(EXIT_FAILURE);
    }

    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            m[i][j]=value;
    return m;
}

Graph GRAPHinit(int V){
    Graph g;
    g=(Graph)malloc(sizeof(struct grafo));
    if(g==NULL) exit(EXIT_FAILURE);
    g->V=V;
    g->E=0;
    g->table=STinit(V);
    g->matAdj=MATRIXinit(g->V, g->V, -1);
    return g;
}


Graph GRAPHload(FILE *fp){
    int V, id1, id2, i, trappola;
    char label1[CAR], label2[CAR];
    Graph g;
    Stanza s;

    fscanf(fp, "%d", &V);
    g=GRAPHinit(V);

    for(i=0; i<V; i++){
        s=STANZAread(fp);
        STinsert(g->table, s);
    }

    while(fscanf(fp, "%s %s %d", label1, label2, &trappola)==3){
        id1=STsearch(g->table, label1);
        id2=STsearch(g->table, label2);
        if(id1!=-1 && id2!=-1)
           GRAPHinsertE(g, id1, id2, trappola);
    }
    return g;
}


void GRAPHinsertE(Graph g, int id1, int id2, int wt){
    if(g->matAdj[id1][id2]==-1){
        g->matAdj[id1][id2]=wt;
        g->matAdj[id2][id1]=wt;
        (g->E)++;
    }
    return;
}


Path GRAPHpathLoad(Graph g, FILE *fp){
       int nStanze, i;
       Path p;
       char label[CAR];
       fscanf(fp, "%d", &nStanze);
       p=PATHcrea(nStanze);
       for(i=0; i<nStanze; i++){
           fscanf(fp, "%s", label);
           p.stanze[i]=STsearch(g->table, label);
       }
       return p;
}


int GRAPHpathCheck(Graph g, Path *p, int M, int PF){
       int i, *visited, mosse=M, vite=PF, ricchezze=0, delta;
       Stanza s;

       visited=(int*)calloc(g->V, sizeof(int));
       if(visited==NULL) exit(EXIT_FAILURE);
       for(i=0; i<p->nStanze; i++){
           if(p->stanze[i]==-1)
               return FALSO;
           s=STgetStanza(g->table, p->stanze[i]);
           if(i==0 && s.livello!=0)
               return FALSO;
           if(i!=0 && s.livello==0)
               return FALSO;
           if(i>0 && g->matAdj[p->stanze[i-1]][p->stanze[i]]==-1)
               return FALSO;
           if(visited[p->stanze[i]]==0){
               visited[p->stanze[i]]=1;
               ricchezze=ricchezze+s.V+s.O;
           }
           if(i>0 && g->matAdj[p->stanze[i-1]][p->stanze[i]]==1)
              vite--;
           if(i>0){
              mosse--;
           }
           if((mosse==0 || vite==0) && (s.livello==1 || s.livello==2)){
               if(ricchezze==0){
                   return FALSO;
               }
               else if(ricchezze >0 && s.livello==1){
                    delta=(int)ceil((float)ricchezze/3.0);
                    ricchezze=ricchezze-delta;
                    mosse=M;
                    vite=PF;
               }
               else if(ricchezze>0 && s.livello==2){
                    delta=(int)ceil((float)ricchezze/2.0);
                    ricchezze=ricchezze-delta;
                    mosse=M;
                    vite=PF;
               }
           }
           else if((mosse==0 || vite==0) && s.livello >=3)
                return FALSO;
       }
       if(g->matAdj[p->stanze[p->nStanze-1]][p->stanze[0]]==-1)
          return FALSO;
       p->ricchezzaTotale=ricchezze;
       return VERO;
}


Path GRAPHpathBest(Graph g, int M, int PF){
       Path sol, bestSol;
       int vite=PF, *visited;

       sol=PATHcrea(M);
       bestSol=PATHcrea(M);
       visited=(int*)calloc(g->V, sizeof(int));
       if(visited==NULL)
           exit(EXIT_FAILURE);

       return GRAPHpathBestR(g, M, PF, vite, &sol, bestSol, visited, 0);
}


Path GRAPHpathBestR(Graph g, int M, int PF, int vite, Path *sol, Path bestSol, int *visited, int pos){
    int i, j;
    Stanza s;
    Boolean primaVisita=FALSO;

    if(vite==0){
        s=STgetStanza(g->table, sol->stanze[pos-1]);
        if(sol->ricchezzaTotale==0)
            return bestSol;
        else{
            if(s.livello>=3)
                return bestSol;
            else if(s.livello==2){
                sol->ricchezzaTotale=sol->ricchezzaTotale - ((int)ceil((float)sol->ricchezzaTotale/2.0));
                vite=PF;
            }
            else if(s.livello==1){
                sol->ricchezzaTotale=sol->ricchezzaTotale - ((int)ceil((float)sol->ricchezzaTotale/3.0));
                vite=PF;
            }
        }
    }

    if(pos>=M){
        if(g->matAdj[sol->stanze[pos-1]][sol->stanze[0]]!=-1 && sol->ricchezzaTotale>bestSol.ricchezzaTotale){
            bestSol.ricchezzaTotale=sol->ricchezzaTotale;
            for(j=0; j<M; j++){
                bestSol.stanze[j]=sol->stanze[j];
            }
        }
        return bestSol;
    }


    for(i=0; i<g->V; i++){
        s=STgetStanza(g->table, i);
        if(pos==0 && s.livello!=0)
            continue;
        if(pos>0 && s.livello==0)
            continue;
        if(pos>0 && g->matAdj[sol->stanze[pos-1]][i]==-1)
            continue;
        if(pos>0 && g->matAdj[sol->stanze[pos-1]][i]==1)
            vite--;
        sol->stanze[pos]=i;
        if(visited[i]==0){
            primaVisita=VERO;
            visited[i]=1;
            sol->ricchezzaTotale=sol->ricchezzaTotale+s.O+s.V;
        }
        bestSol=GRAPHpathBestR(g, M, PF, vite, sol, bestSol, visited, pos+1);
        if(primaVisita==VERO){
            primaVisita=FALSO;
            visited[i]=0;
            sol->ricchezzaTotale=sol->ricchezzaTotale-s.O-s.V;
        }
        if(pos>0 && g->matAdj[sol->stanze[pos-1]][i]==1)
            vite++;
    }
    return bestSol;
}



static void free2D(int **m, int nr){
    int i;
    if(m!=NULL){
        for(i=0; i<nr; i++){
            if(m[i]!=NULL)
                free(m[i]);
        }
        free(m);
    }
    return;
}

void GRAPHfree(Graph g){
    if(g!=NULL){
        STfree(g->table);
        free2D(g->matAdj, g->V);
        free(g);
    }
    return;
}
