#include "percorso.h"
#include <limits.h>

/* 
   Inizializza la mossa
*/
Mossa MOSSAcreate(int riga, int colonna) {
   Mossa m;
   m.riga=riga;
   m.colonna=colonna;
   return m;
}

/* 
   Legge la mossa da file
*/
Mossa MOSSAread(FILE *f) {
   Mossa m;
   fscanf(f, "%d %d", &m.riga, &m.colonna);
   return m;
}

/*
   Stampa la mossa
*/
void MOSSAprint(Mossa m, FILE *f) {
   fprintf(f, "(%d, %d)\n", m.riga, m.colonna);
   return;
}



/*
   Inizializza il percorso
*/
Percorso PERCORSOinit(int maxD) {
   Percorso p;
   p.maxD=maxD;
   p.dim=0;
   p.mosse=(Mossa*)malloc(maxD*sizeof(Mossa));
   if(p.mosse==NULL)
      exit(EXIT_FAILURE);
   return p;
}

/*
   Legge il percorso da file
*/
Percorso PERCORSOread(FILE *f) {
   int i, dim;
   Percorso p;
   fscanf(f, "%d", &dim);
   p=PERCORSOinit(dim);
   p.dim=dim;
   for(i=0; i<dim; i++)
      p.mosse[i]=MOSSAread(f);
   return p;
}

/*
   Controlla che un determinato percorso sia
   valido per una determinata griglia
*/
Boolean PERCORSOcheck(Percorso p, Griglia g, int *cambi, int AreaBianchi) {
   int i;
   Direzione dirPrec=-1, dirAttuale;

   /*
      Controlla che riga e colonna della prima 
      mossa siano nella prima cella in alto
      a sinistra 
   */
   if(p.mosse[0].riga!=0 || p.mosse[0].colonna!=0)
      return FALSO;

   (*cambi)=0;
   for(i=1; i<p.dim; i++){
      /* Controllo se mossa è dentro la griglia */
      if(p.mosse[i].riga<0 || p.mosse[i].riga>=g.nr || p.mosse[i].colonna<0 || p.mosse[i].colonna>=g.nc)
         return FALSO;

      /* Se la cella è nera, la mossa non ha una partenza valida */
      if(g.griglia[p.mosse[i].riga][p.mosse[i].colonna]==NERO)
         return FALSO;

      /* 
         Se la mossa precedente alla corrente ha riga e 
         colonna diversa alla corrente, vuol dire che
         sono cambiati entrambi, e quindi la mossa è in
         diagonale e non è valida
      */
      if(p.mosse[i].riga!=p.mosse[i-1].riga && p.mosse[i].colonna!=p.mosse[i-1].colonna)
         return FALSO;

      /* Direzione SUD */
      if(p.mosse[i].riga==p.mosse[i-1].riga+1)
         dirAttuale=S;
      /* Direzione NORD */
      else if(p.mosse[i].riga==p.mosse[i-1].riga-1)
         dirAttuale=N;
      /* Direzione EST */
      else if(p.mosse[i].colonna==p.mosse[i-1].colonna+1)
         dirAttuale=E;
      /* Direzione OVEST */
      else if(p.mosse[i].colonna==p.mosse[i-1].colonna-1)
         dirAttuale=O;
      /* 
         Se la direzione è stata cambiata dalla precedente, 
         allora si ha un cambio di direzione
      */
      if(dirPrec!=-1 && dirAttuale!=dirPrec)
         (*cambi)++;
      dirPrec=dirAttuale;
   }

   /* 
      Se l'area totale dei bianchi è diversa dalla dimensione
      del percorso, non è il percorso semplice che passa
      per tutte le celle bianche
   */
   if(AreaBianchi!=p.dim)
      return FALSO;
   return VERO;
}

/* 
   Inserisci nel percorso, aggiornando la dimensione
   massima al doppio della dimensione massima attuale
*/
void PERCORSOinsert(Percorso *p, Mossa m) {
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

/*
   Cancella una mossa dal percorso
*/
void PERCORSOdelete(Percorso *p) {
   (p->dim)--;
   return;
}

/*
   Risolve cercando il percorso migliore in maniera ricorsiva
*/
static void solveR(Griglia *g, Percorso *sol, Percorso *bestSol, int *min, int riga, int colonna, int areaBianchi, Boolean *trovato) {
   int cambi, i;
   Boolean exit=VERO;


   g->griglia[riga][colonna]=OCCUPATO;
   PERCORSOinsert(sol, MOSSAcreate(riga, colonna));

   /* 
      Se andando avanti nella riga la cella è nella griglia
      ed è bianca, allora continua la soluzione per questa 
      direzione
   */
   if(riga+1>=0 && riga+1<g->nr && g->griglia[riga+1][colonna]==BIANCO){
      solveR(g, sol, bestSol, min, riga+1, colonna, areaBianchi, trovato);
      exit=FALSO;
   }

   /* 
      Se andando indietro nella riga la cella è nella griglia
      ed è bianca, allora continua la soluzione per questa 
      direzione
   */
   if(riga-1>=0 && riga-1<g->nr && g->griglia[riga-1][colonna]==BIANCO){
      solveR(g, sol, bestSol, min, riga-1, colonna, areaBianchi, trovato);
      exit=FALSO;
   }

   /* 
      Se andando avanti nella colonna la cella è nella griglia
      ed è bianca, allora continua la soluzione per questa 
      direzione
   */
   if(colonna+1>=0 && colonna+1<g->nc && g->griglia[riga][colonna+1]==BIANCO){
      solveR(g, sol, bestSol, min, riga, colonna+1, areaBianchi, trovato);
      exit=FALSO;
   }

   /* 
      Se andando indietro nella riga la cella è nella griglia
      ed è bianca, allora continua la soluzione per questa 
      direzione
   */
   if(colonna-1>=0 && colonna-1<g->nc && g->griglia[riga][colonna-1]==BIANCO){
      solveR(g, sol, bestSol, min, riga, colonna-1, areaBianchi, trovato);
      exit=FALSO;
   }

   /* 
      Se nessuna delle altre opzioni è stata valutata,
      non si può andare avanti e bisogna controllare
      il percorso, la sua lunghezza e il suo numero di cambi
   */
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

   /* Backtrack sul percorso */
   g->griglia[riga][colonna]=BIANCO;
   PERCORSOdelete(sol);
   return;

}

/*
   NB: "Disposizioni semplici"
*/
void PERCORSOsolve(Griglia g){
   Percorso sol, bestSol;
   int min=INT_MAX;
   Boolean trovato=FALSO;

   sol=PERCORSOinit(g.nr*g.nc);
   bestSol=PERCORSOinit(g.nr*g.nc);

   solveR(&g, &sol, &bestSol, &min, 0, 0, GRIGLIAareaBianchi(g), &trovato);

   if(trovato==VERO) {
      printf("La soluzione ottima prevede %d cambi di direzione.\n\n", min);
      printf("~~~PERCORSO:~~~\n");
      PERCORSOprint(bestSol, stdout);

   } else {
      printf("Soluzione non trovata.\n");
   }

   PERCORSOclear(sol);
   PERCORSOclear(bestSol);
   return;
}

/* 
   Stampa il percorso
*/
void PERCORSOprint(Percorso p, FILE *f) {
   int i;
   for(i=0; i<p.dim; i++)
      MOSSAprint(p.mosse[i], f);
   return;
}

/* 
   Dealloca il percorso mossa per mossa
*/
void PERCORSOclear(Percorso p){
   if(p.mosse!=NULL)
      free(p.mosse);
   return;
}
