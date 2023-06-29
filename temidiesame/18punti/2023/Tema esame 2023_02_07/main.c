#include <stdio.h>
#include <stdlib.h>
#include "bonus.h"
#include "grid.h"

typedef struct{
   Token t;
   int riga, colonna;
}Scelta;

typedef struct{
   Scelta *scelte;
   int dim;
}Soluzione;

int **malloc2D(int nr, int nc, int val);
void free2D(int **mat, int nr);
Soluzione readProposta(char *nomeFile);
Boolean verifica(Soluzione proposta, Grid griglia, Bonus b, int L, int *bonus);
void solve(Bonus b, Grid griglia, int L);
void dispSemp(Bonus b, Grid griglia, int L, Soluzione *sol, Token *bestBuffer, int**mark, int *max, int pos, int riga, int colonna);

int main()
{
    FILE *fg, *fb1, *fb2;
    Grid griglia;
    Bonus b1, b2;
    Soluzione proposta1, proposta2;
    int L1=3, L2=4, bonus;

    fg=fopen("grid.txt", "r");
    if(fg==NULL) exit(EXIT_FAILURE);
    griglia=GRIDread(fg);

    fb1=fopen("bonus1.txt", "r");
    if(fb1==NULL) exit(EXIT_FAILURE);
    b1=BONUSread(fb1);

    fb2=fopen("bonus2.txt", "r");
    if(fb2==NULL) exit(EXIT_FAILURE);
    b2=BONUSread(fb2);

    proposta1=readProposta("mosse.txt");
    proposta2=readProposta("mosse1.txt");

    printf("---PROBLEMA DI VERIFICA 1:---\n");
    if(verifica(proposta1, griglia, b1, L1, &bonus)==VERO){
        printf("La soluzione e' valida. Bonus: %d\n\n", bonus);
    }
    else{
        printf("La soluzione non e' valida.\n\n");
    }

    printf("---PROBLEMA DI VERIFICA 2:---\n");
    if(verifica(proposta2, griglia, b2, L2, &bonus)==VERO){
        printf("La soluzione e' valida. Bonus: %d\n\n", bonus);
    }
    else{
        printf("La soluzione non e' valida.\n\n");
    }

    printf("---PROBLEMA DI RICERCA 1:---\n");
    solve(b1, griglia, L1);
    printf("\n\n");

    printf("---PROBLEMA DI RICERCA 2:---\n");
    solve(b2, griglia, L2);
    printf("\n");

    GRIDclear(&griglia);
    BONUSclear(&b1);
    BONUSclear(&b2);
    free(proposta1.scelte);
    free(proposta2.scelte);
    fclose(fg);
    fclose(fb1);
    fclose(fb2);
    return 0;
}



Soluzione readProposta(char *nomeFile){
    FILE *f;
    Soluzione sol;
    int i;
    f=fopen(nomeFile, "r");
    if(f==NULL) exit(EXIT_FAILURE);
    fscanf(f, "%d", &sol.dim);
    sol.scelte=(Scelta*)malloc(sol.dim*sizeof(Scelta));
    if(sol.scelte==NULL) exit(EXIT_FAILURE);
    for(i=0; i<sol.dim; i++){
        sol.scelte[i].t=TOKENread(f);
        fscanf(f, "%d %d", &sol.scelte[i].riga, &sol.scelte[i].colonna);
    }
    return sol;
}


//Il file è cosi strutturato:
//Prima riga: numero di token N
//Seguono N righe composte da <token> <riga nella matrice> <colonna nella matrice>
Boolean verifica(Soluzione proposta, Grid griglia, Bonus b, int L, int *bonus){
    int i, index=0, valBonus=0;
    Token *buffer;
    buffer=(Token*)malloc(L*sizeof(Token));
    if(buffer==NULL) exit(EXIT_FAILURE);
    if(L!=proposta.dim)
       return FALSO;
    if(proposta.scelte[0].riga!=0)
      return FALSO;
    if(TOKENcompare(proposta.scelte[0].t, griglia.grid[proposta.scelte[0].riga][proposta.scelte[0].colonna])!=0)
       return FALSO;
    buffer[index++]=proposta.scelte[0].t;
    for(i=1; i<L; i++){
       if(i%2!=0 && proposta.scelte[i].colonna!=proposta.scelte[i-1].colonna)
          return FALSO;
       else if(i%2==0 && proposta.scelte[i].riga!=proposta.scelte[i-1].riga)
          return FALSO;
       if(TOKENcompare(proposta.scelte[i].t, griglia.grid[proposta.scelte[i].riga][proposta.scelte[i].colonna])!=0)
          return FALSO;
       buffer[index++]=proposta.scelte[i].t;
    }
    for(i=0; i<b.dim; i++){
       if(TOKENisSubToken(buffer, L, b.tbonus[i].t, b.tbonus[i].dim)==VERO){
          valBonus+=b.tbonus[i].bonus;
       }
    }
    *bonus=valBonus;
    return VERO;
}


void solve(Bonus b, Grid griglia, int L){
    Soluzione sol;
    int **mark, max=0, i;
    Token *bestBuffer;

    sol.dim=L;

    sol.scelte=(Scelta*)malloc(L*sizeof(Scelta));
    if(sol.scelte==NULL) exit(EXIT_FAILURE);

    bestBuffer=(Token*)malloc(L*sizeof(Token));
    if(bestBuffer==NULL) exit(EXIT_FAILURE);

    mark=malloc2D(griglia.nr, griglia.nc, 0);

    dispSemp(b, griglia, L, &sol, bestBuffer, mark, &max, 0, 0, 0);

    printf("BestSolution:\n");
    printf("Buffer: ");
    for(i=0; i<L; i++)
       TOKENprint(bestBuffer[i], stdout);
    printf("\nBonus: %d", max);

    free(sol.scelte);
    free(bestBuffer);
    free2D(mark, griglia.nr);
    return;
}


void dispSemp(Bonus b, Grid griglia, int L, Soluzione *sol, Token *bestBuffer, int**mark, int *max, int pos, int riga, int colonna){
    int bonus, i, r, c;
    if(pos>=L){
       if(verifica(*sol, griglia, b, L, &bonus)==VERO && bonus > (*max)){
          (*max)=bonus;
          for(i=0; i<L; i++)
            bestBuffer[i]=sol->scelte[i].t;
       }
       return;
    }
    if(pos%2!=0){
       for(r=0; r<griglia.nr; r++){
          if(mark[r][colonna]==0){
             mark[r][colonna]=1;
             sol->scelte[pos].t=griglia.grid[r][colonna];
             sol->scelte[pos].riga=r;
             sol->scelte[pos].colonna=colonna;
             dispSemp(b, griglia, L, sol, bestBuffer, mark, max, pos+1, r, colonna);
             mark[r][colonna]=0;
          }
       }
    }
    else if(pos%2==0){
       for(c=0; c<griglia.nc; c++){
          if(mark[riga][c]==0){
             mark[riga][c]=1;
             sol->scelte[pos].t=griglia.grid[riga][c];
             sol->scelte[pos].riga=riga;
             sol->scelte[pos].colonna=c;
             dispSemp(b, griglia, L, sol, bestBuffer, mark, max, pos+1, riga, c);
             mark[riga][c]=0;
          }
       }
    }
    return;
}


int **malloc2D(int nr, int nc, int val){
    int **mat;
    int i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
       mat[i]=(int*)malloc(nc*sizeof(int));
       if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            mat[i][j]=val;
        }
    }
    return mat;
}


void free2D(int **mat, int nr){
    int i;
    if(mat!=NULL){
       for(i=0; i<nr; i++){
          if(mat[i]!=NULL)
             free(mat[i]);
       }
       free(mat);
    }
    return;
}
