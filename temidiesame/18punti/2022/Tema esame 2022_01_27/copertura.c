#include "copertura.h"
#include <limits.h>

//REGIONE
Regione REGIONEcrea(int riga, int colonna, int base, int altezza){
    Regione r;
    r.riga=riga;
    r.colonna=colonna;
    r.base=base;
    r.altezza=altezza;
    return r;
}


Regione REGIONEsetNull(){
    Regione r;
    r.riga=-1;
    r.colonna=-1;
    r.base=-1;
    r.altezza=-1;
    return r;
}


Regione REGIONEread(FILE *f){
    Regione r;
    if(fscanf(f, "%d %d %d %d", &r.riga, &r.colonna, &r.base, &r.altezza)==4)
       return r;
    return REGIONEsetNull();
}


Boolean REGIONEisNull(Regione r){
    if(r.riga==-1 && r.colonna==-1 &&r.base==-1 && r.altezza==-1)
       return VERO;
    return FALSO;
}


void REGIONEprint(Regione r, FILE *f){
    fprintf(f, "(%d, %d) %s- Lato: %d", r.riga, r.colonna, (r.riga>9 || r.colonna>9)?"":" ", r.base);
    return;
}



//COPERTURA
Copertura COPERTURAinit(int maxD){
    Copertura c;
    c.maxD=maxD;
    c.dim=0;
    c.regioni=(Regione*)malloc(maxD*sizeof(Regione));
    if(c.regioni==NULL){
        printf("Errore di allocazione.");
        exit(EXIT_FAILURE);
    }
    return c;
}


Copertura COPERTURAread(FILE *f){
    Copertura c;
    Regione r;
    c=COPERTURAinit(1);
    r=REGIONEread(f);
    while(REGIONEisNull(r)==FALSO){
       COPERTURAinsert(&c, r);
       r=REGIONEread(f);
    }
    return c;
}


void COPERTURAinsert(Copertura *c, Regione r){
    if(c->maxD==c->dim){
       c->maxD=c->maxD*2;
       c->regioni=realloc(c->regioni, c->maxD*sizeof(Regione));
       if(c->regioni==NULL){
          printf("Errore di allocazione.");
          exit(EXIT_FAILURE);
       }
    }
    c->regioni[c->dim]=r;
    (c->dim)++;
    return;
}


void COPERTURAdelete(Copertura *c){
    (c->dim)--;
    return;
}


Boolean COPERTURAcheck(Copertura c, Griglia g, int *nRegioni, int areaBianco){
    int i, area=0;
    for(i=0; i<c.dim; i++){
        if(c.regioni[i].base!=c.regioni[i].altezza)
           return FALSO;
        if(c.regioni[i].riga <0 || c.regioni[i].riga>=g.nr)
           return FALSO;
        if(c.regioni[i].colonna<0 || c.regioni[i].colonna>=g.nc)
           return FALSO;
        if(c.regioni[i].riga+c.regioni[i].altezza>g.nr)
           return FALSO;
        if(c.regioni[i].colonna+c.regioni[i].base>g.nc)
           return FALSO;
        if(GRIGLIAcheckRegione(g, c.regioni[i].riga, c.regioni[i].colonna, c.regioni[i].base, c.regioni[i].altezza)==FALSO)
           return FALSO;
        GRIGLIAfillRegione(&g, c.regioni[i].riga, c.regioni[i].colonna, c.regioni[i].base, c.regioni[i].altezza, i+2);
        area=area+(c.regioni[i].base*c.regioni[i].altezza);
    }
    if(area!=areaBianco)
       return FALSO;
    (*nRegioni)=c.dim;
    return VERO;
}


static void solveR(Griglia *g, Copertura *sol, Copertura *bestSol, int *min, int currNumRegion, int pos){
    int i, maxAreaBianco, j;
    int r, c;

    if(currNumRegion > (*min)){
        return;
    }

    if(pos>=(g->nr*g->nc)){
       if(currNumRegion < (*min)){
          (*min)=currNumRegion;
          bestSol->dim=0;
          for(j=0; j<currNumRegion; j++){
             COPERTURAinsert(bestSol, sol->regioni[j]);
          }
       }
       return;
    }

    r=pos/g->nc;
    c=pos%g->nc;

    if(g->griglia[r][c]!=BIANCO){
       solveR(g, sol, bestSol, min, currNumRegion, pos+1);
       return;
    }
    maxAreaBianco=GRIGLIAgetMaxAreaBianco(*g, r, c);
    for(i=maxAreaBianco; i>=1; i--){
       COPERTURAinsert(sol, REGIONEcrea(r, c, i, i));
       GRIGLIAfillRegione(g, r, c, i, i, currNumRegion+2);
       currNumRegion=currNumRegion+1;
       solveR(g, sol, bestSol, min, currNumRegion, pos+1);
       COPERTURAdelete(sol);
       currNumRegion=currNumRegion-1;
       GRIGLIAdeleteRegione(g, r, c, i, i);
    }
    return;
}


void COPERTURAsolve(Griglia g){
    Copertura sol, bestSol;
    int min=INT_MAX, currNumRegion=0;

    sol=COPERTURAinit(1);
    bestSol=COPERTURAinit(1);

    solveR(&g, &sol, &bestSol, &min, currNumRegion, 0);

    printf("La soluzione ottima utilizza %d regioni quadrate per coprire l'intera regione bianca.\n\n", bestSol.dim);
    printf("~~~ELENCO REGIONI:~~~\n");
    COPERTURAprint(bestSol, stdout);

    COPERTURAclear(sol);
    COPERTURAclear(bestSol);
    return;
}


void COPERTURAprint(Copertura c, FILE *f){
   int i;
   for(i=0; i<c.dim; i++){
      fprintf(f, "Regione %d: %s", i+1, (i+1>9)?"":" ");
      REGIONEprint(c.regioni[i], f);
      fprintf(f, "\n");
   }
   return;
}


void COPERTURAclear(Copertura c){
    if(c.regioni!=NULL){
        free(c.regioni);
    }
    return;
}
