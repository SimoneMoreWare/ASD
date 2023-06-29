#include "percorso.h"
#include <limits.h>

//MOSSA
Mossa MOSSAcreate(int riga, int colonna){
    Mossa m;
    m.riga=riga;
    m.colonna=colonna;
    return m;
}


Mossa MOSSAread(FILE *f){
    Mossa m;
    fscanf(f, "%d %d", &m.riga, &m.colonna);
    return m;
}


void MOSSAprint(Mossa m, FILE *f){
    fprintf(f, "(%d, %d)\n", m.riga, m.colonna);
    return;
}



//PERCORSO
Percorso PERCORSOinit(int maxD){
    Percorso p;
    p.maxD=maxD;
    p.dim=0;
    p.mosse=(Mossa*)malloc(maxD*sizeof(Mossa));
    if(p.mosse==NULL)
       exit(EXIT_FAILURE);
    return p;
}


Percorso PERCORSOread(FILE *f){
    int i, dim;
    Percorso p;
    fscanf(f, "%d", &dim);
    p=PERCORSOinit(dim);
    p.dim=dim;
    for(i=0; i<dim; i++)
       p.mosse[i]=MOSSAread(f);
    return p;
}


Boolean PERCORSOcheck(Percorso p, Griglia g, int *cambi, int AreaBianchi){
    int i;
    Direzione dirPrec=-1, dirAttuale;

    if(p.mosse[0].riga!=0 || p.mosse[0].colonna!=0)
       return FALSO;

    (*cambi)=0;
    for(i=1; i<p.dim; i++){
       if(p.mosse[i].riga<0 || p.mosse[i].riga>=g.nr || p.mosse[i].colonna<0 || p.mosse[i].colonna>=g.nc)
          return FALSO;
       if(g.griglia[p.mosse[i].riga][p.mosse[i].colonna]==NERO)
         return FALSO;
       if(p.mosse[i].riga!=p.mosse[i-1].riga && p.mosse[i].colonna!=p.mosse[i-1].colonna)
          return FALSO;
       if(p.mosse[i].riga==p.mosse[i-1].riga+1)
          dirAttuale=S;
       else if(p.mosse[i].riga==p.mosse[i-1].riga-1)
          dirAttuale=N;
       else if(p.mosse[i].colonna==p.mosse[i-1].colonna+1)
          dirAttuale=E;
       else if(p.mosse[i].colonna==p.mosse[i-1].colonna-1)
          dirAttuale=O;
       if(dirPrec!=-1 && dirAttuale!=dirPrec)
          (*cambi)++;
        dirPrec=dirAttuale;
    }
    if(AreaBianchi!=p.dim)
        return FALSO;
    return VERO;
}


void PERCORSOinsert(Percorso *p, Mossa m){
    if(p->dim==p->maxD){
       p->maxD=p->maxD*2;
       p->mosse=realloc(p->mosse, p->maxD*sizeof(Mossa));
       if(p->mosse==NULL)
          exit(EXIT_FAILURE);
    }
    p->mosse[p->dim]=m;
    (p->dim)++;
    return;
}


void PERCORSOdelete(Percorso *p){
    (p->dim)--;
    return;
}


static void solveR(Griglia *g, Percorso *sol, Percorso *bestSol, int *min, int riga, int colonna, int areaBianchi, Boolean *trovato){
    int cambi, i;
    Boolean exit=VERO;

    g->griglia[riga][colonna]=OCCUPATO;
    PERCORSOinsert(sol, MOSSAcreate(riga, colonna));

    if(riga+1>=0 && riga+1<g->nr && g->griglia[riga+1][colonna]==BIANCO){
       solveR(g, sol, bestSol, min, riga+1, colonna, areaBianchi, trovato);
       exit=FALSO;
    }

    if(riga-1>=0 && riga-1<g->nr && g->griglia[riga-1][colonna]==BIANCO){
       solveR(g, sol, bestSol, min, riga-1, colonna, areaBianchi, trovato);
       exit=FALSO;
    }

    if(colonna+1>=0 && colonna+1<g->nc && g->griglia[riga][colonna+1]==BIANCO){
       solveR(g, sol, bestSol, min, riga, colonna+1, areaBianchi, trovato);
       exit=FALSO;
    }

    if(colonna-1>=0 && colonna-1<g->nc && g->griglia[riga][colonna-1]==BIANCO){
       solveR(g, sol, bestSol, min, riga, colonna-1, areaBianchi, trovato);
       exit=FALSO;
    }
    if(exit==VERO){
       if(PERCORSOcheck(*sol, *g, &cambi, areaBianchi)==VERO && cambi < (*min)){
          (*trovato)=VERO;
          (*min)=cambi;
          bestSol->dim=sol->dim;
          for(i=0; i<sol->dim; i++){
             bestSol->mosse[i]=sol->mosse[i];
          }
       }
    }
    g->griglia[riga][colonna]=BIANCO;
    PERCORSOdelete(sol);
    return;

}


void PERCORSOsolve(Griglia g){
   Percorso sol, bestSol;
   int min=INT_MAX;
   Boolean trovato=FALSO;

   sol=PERCORSOinit(g.nr*g.nc);
   bestSol=PERCORSOinit(g.nr*g.nc);

   solveR(&g, &sol, &bestSol, &min, 0, 0, GRIGLIAareaBianchi(g), &trovato);

   if(trovato==VERO){
       printf("La soluzione ottima prevede %d cambi di direzione.\n\n", min);
       printf("~~~PERCORSO:~~~\n");
       PERCORSOprint(bestSol, stdout);

   }
   else{
      printf("Soluzione non trovata.\n");
   }
   PERCORSOclear(sol);
   PERCORSOclear(bestSol);
   return;
}


void PERCORSOprint(Percorso p, FILE *f){
    int i;
    for(i=0; i<p.dim; i++)
       MOSSAprint(p.mosse[i], f);
    return;
}


void PERCORSOclear(Percorso p){
    if(p.mosse!=NULL)
       free(p.mosse);
    return;
}
