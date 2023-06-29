#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "programma.h"
#define R 4
#define S 4
#define EMPTY -1

void solve(Articoli a, ST argomenti);
void solveR(Articoli a, ST argomenti, int nArticoli, int *min, int *bestNA, int *bestNV, Programma *sol, Programma *bestSol, int pos);
Boolean checkMultiSlot(Programma p, int room, int slot, int nSlot);

int main()
{
   Articoli a;
   ST argomenti;
   FILE *f;

   f=fopen("articoli.txt", "r");

   if(f==NULL)
      exit(EXIT_FAILURE);

   a=ARTICOLIread(f);
   argomenti=ARTICOLIgetArgomenti(a);

   printf("---PROBLEMA DI VERIFICA:---\n");
   if(PROGRAMMAcheck(R, S, EMPTY, a, "proposta.txt")==VERO){
       printf("Soluzione valida.\n\n");
   }
   else{
       printf("Soluzione non valida.\n\n");
   }

   printf("\n---PROBLEMA DI RICERCA:---\n");
   solve(a, argomenti);

   fclose(f);
   ARTICOLIfree(a);
   STfree(argomenti);
   return 0;
}




void solve(Articoli a, ST argomenti){
    Programma sol, bestSol;
    int min=INT_MAX, nArticoli, NA, NV;

    sol=PROGRAMMAcrea(R, S, EMPTY);
    bestSol=PROGRAMMAcrea(R, S, EMPTY);
    nArticoli=ARTICOLIgetNumArticoli(a);

    solveR(a, argomenti, nArticoli, &min, &NA, &NV, &sol, &bestSol, 0);

    printf("Best solution:\n\n");
    PROGRAMMAprint(bestSol, a, EMPTY, stdout);
    printf("\nNA: %d - NV: %d\n", NA, NV);

    PROGRAMMAclear(sol);
    PROGRAMMAclear(bestSol);
    return;
}




void solveR(Articoli a, ST argomenti, int nArticoli, int *min, int *bestNA, int *bestNV, Programma *sol, Programma *bestSol, int pos){
    int room, slot, NA, NV, i, j;
    Articolo ar, prec, succ;

    if(pos>=nArticoli){
        NA=PROGRAMMAargomentiDistinti(*sol, argomenti, a);
        NV=PROGRAMMAslotVuoti(*sol, EMPTY);
        if((NA+NV) < (*min)){
            (*bestNA) = NA;
            (*bestNV) = NV;
            (*min) = (NA+NV);
            for(i=0; i<R; i++){
                for(j=0; j<S; j++){
                    bestSol->mat[i][j]=sol->mat[i][j];
                }
            }
        }
        return;
    }

    ar=ARTICOLIgetArticolo(a, pos);
    for(room=0; room < R; room++){
        for(slot=0; slot < S; slot++){
            if(sol->mat[room][slot]!=EMPTY)
                continue;
            if(slot+ar.slot>S)
                continue;
            if(room>0 && sol->mat[room-1][slot]!=EMPTY){
                prec=ARTICOLIgetArticolo(a, sol->mat[room-1][slot]);
                if(strcmp(ar.relatore, prec.relatore)==0){
                    continue;
                }
            }
            if(room<(R-1) && sol->mat[room+1][slot]!=EMPTY){
                succ=ARTICOLIgetArticolo(a, sol->mat[room+1][slot]);
                if(strcmp(ar.relatore, succ.relatore)==0){
                    continue;
                }
            }
            if(ar.slot>1 && checkMultiSlot(*sol, room, slot, ar.slot)==FALSO){
                continue;
            }
            PROGRAMMAinsertArticolo(sol, pos, room, slot, ar.slot);
            solveR(a, argomenti, nArticoli, min, bestNA, bestNV, sol, bestSol, pos+1);
            PROGRAMMAeliminaArticolo(sol, EMPTY, room, slot, ar.slot);
        }
    }
    return;
}



Boolean checkMultiSlot(Programma p, int room, int slot, int nSlot){
    int i;
    for(i=slot; i<slot+nSlot; i++){
        if(p.mat[room][i]!=EMPTY)
            return FALSO;
    }
    return VERO;
}
