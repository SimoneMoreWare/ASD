#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sol.h"
#include "grid.h"
#include "words.h"
#define EMPTY 0
#define OCCUPATO 1
#define INESISTENTE -1

typedef enum{VERIFICA, RICERCA}Problema;

void getParolaMatrice(char *parola, int rI, int cI, int len, char **mat, int nr, int nc, char direzione);
Boolean verifica(Sol proposta, Grid g, Words w, Problema p);
void solve(Grid g, Words w);
void solveR(Grid g, Words w, Sol *sol, Sol *bestSol, int *max, int **visited, int punteggio, int pos, int start);
Posizione whereIsInTheMatrix(Grid g, Sol sol, char *word, int len, int **visited);
void addWord(int **visited, int nr, int nc, int rI, int cI, char direzione, int len);
void deleteWord(int **visited, int nr, int nc, int rI, int cI, char direzione, int len);
int **malloc2D(int nr, int nc, int value);
void free2D(int **mat, int nr);
Boolean checkSostituzioni(Sol proposta, int rI, int cI, char dir);

int main()
{
    Grid g;
    Words w;
    Sol proposta;
    FILE *f1, *f2, *f3;

    f1=fopen("griglia.txt", "r");
    if(f1==NULL)
        exit(EXIT_FAILURE);

    f2=fopen("parole.txt", "r");
    if(f2==NULL)
        exit(EXIT_FAILURE);

    f3=fopen("proposta.txt", "r");
    if(f3==NULL)
        exit(EXIT_FAILURE);

    g=GRIDread(f1);

    w=WORDSread(f2);

    proposta=SOLread(f3);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(verifica(proposta, g, w, VERIFICA)==VERO){
        printf("Soluzione valida.\n\n\n");
    }
    else{
       printf("Soluzione non valida.\n\n\n");
    }

    printf("---PROBLEMA DI RICERCA:---\n");
    solve(g, w);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    GRIDclear(g);
    WORDSclear(w);
    SOLclear(proposta);
    return 0;
}




void getParolaMatrice(char *parola, int rI, int cI, int len, char **mat, int nr, int nc, char direzione){
    int riga, colonna, indexP=0;
    switch(direzione){
       case 'O':
          for(colonna=cI; colonna<cI+len && colonna<nc; colonna++){
             parola[indexP++]=mat[rI][colonna];
          }
          break;
       case 'V':
          for(riga=rI; riga<rI+len && riga<nr; riga++){
             parola[indexP++]=mat[riga][cI];
          }
          break;
       case 'D':
          for(riga=rI, colonna=cI; riga<rI+len && colonna<cI+len && colonna<nc && riga<nr; riga++, colonna++){
             parola[indexP++]=mat[riga][colonna];
          }
          break;
    }
    parola[indexP]='\0';
    return;
}




Boolean verifica(Sol proposta, Grid g, Words w, Problema p){
    int scelta, parola, count=0, i, j;
    char word[16];


    //Check: parole nella soluzione fanno parte della lista
    for(scelta=0; scelta<proposta.nScelte; scelta++){
        for(parola=0; parola<w.nParole; parola++){
            if(strcmp(w.parole[parola].parola, proposta.scelte[scelta].parola)==0){
                count++;
                break;
            }
        }
    }
    if(count!=proposta.nScelte)
        return FALSO;

    //Check: le parole sono presenti nella griglia+rispettano i vincoli di orientamento
    for(i=0; i<proposta.nScelte; i++){
        if(proposta.scelte[i].p.r<0 || proposta.scelte[i].p.r>=g.nr || proposta.scelte[i].p.c<0 || proposta.scelte[i].p.c>=g.nc)
            return FALSO;
        if(proposta.scelte[i].p.dir!='O' && proposta.scelte[i].p.dir!='V' && proposta.scelte[i].p.dir!='D')
            return FALSO;
        if(proposta.scelte[i].p.dir=='O' && proposta.scelte[i].p.c+strlen(proposta.scelte[i].parola)>g.nc)
            return FALSO;
        if(proposta.scelte[i].p.dir=='V' && proposta.scelte[i].p.r+strlen(proposta.scelte[i].parola)>g.nr)
            return FALSO;
        if(proposta.scelte[i].p.dir=='D' && proposta.scelte[i].p.c+strlen(proposta.scelte[i].parola)>g.nc && proposta.scelte[i].p.r+strlen(proposta.scelte[i].parola)>g.nr)
            return FALSO;
        getParolaMatrice(word, proposta.scelte[i].p.r, proposta.scelte[i].p.c, strlen(proposta.scelte[i].parola), g.griglia, g.nr, g.nc, proposta.scelte[i].p.dir);
        if(strcmp(word, proposta.scelte[i].parola)!=0)
            return FALSO;
    }


    //Check: vincoli di sovrapposizione
    for(i=0; i<proposta.nScelte; i++){
       for(j=0; j<proposta.nScelte; j++){
          if(strcmp(proposta.scelte[i].parola, proposta.scelte[j].parola)!=0 && proposta.scelte[i].p.dir==proposta.scelte[j].p.dir){
             switch(proposta.scelte[i].p.dir){
                case 'O':
                   if(proposta.scelte[i].p.r==proposta.scelte[j].p.r && proposta.scelte[i].p.c <= proposta.scelte[j].p.c){
                      if(proposta.scelte[j].p.c < proposta.scelte[i].p.c + strlen(proposta.scelte[i].parola)-1)
                         return FALSO;
                   }
                   break;
                case 'V':
                   if(proposta.scelte[i].p.c==proposta.scelte[j].p.c && proposta.scelte[i].p.r <= proposta.scelte[j].p.r){
                      if(proposta.scelte[j].p.r < proposta.scelte[i].p.r + strlen(proposta.scelte[i].parola)-1)
                         return FALSO;
                   }
                   break;
                case 'D':
                   if((proposta.scelte[i].p.r-proposta.scelte[i].p.c) == (proposta.scelte[j].p.r-proposta.scelte[j].p.c) && proposta.scelte[i].p.c <= proposta.scelte[j].p.c && proposta.scelte[i].p.r <= proposta.scelte[j].p.r){
                      if(proposta.scelte[j].p.c < proposta.scelte[i].p.c + strlen(proposta.scelte[i].parola)-1 && proposta.scelte[j].p.r < proposta.scelte[i].p.r + strlen(proposta.scelte[i].parola)-1)
                         return FALSO;
                   }
                   break;
             }
          }
       }
    }
    return VERO;
}




void solve(Grid g, Words w){
    int max=0, punteggio=0, *mark, **visited;
    Sol sol, bestSol;

    sol=SOLcrea(w.nParole);
    bestSol=SOLcrea(w.nParole);
    visited=malloc2D(g.nr, g.nc, EMPTY);

    mark=calloc(w.nParole, sizeof(int));
    if(mark==NULL)
        exit(EXIT_FAILURE);

    WORDSorder(w);

    solveR(g, w, &sol, &bestSol, &max, visited, punteggio, 0, 0);

    printf("Best Solution:\n");
    printf("Massimo punteggio: %d - Numero Parole: %d\n\n", max, bestSol.nScelte);
    printf("~~~ELENCO PAROLE:~~~\n");
    SOLprint(bestSol, stdout);

    SOLclear(sol);
    SOLclear(bestSol);
    free2D(visited, g.nr);
    return;
}




void solveR(Grid g, Words w, Sol *sol, Sol *bestSol, int *max, int **visited, int punteggio, int pos, int start){
    int j, i, len;
    Posizione p;

    if(punteggio > (*max) || (punteggio == (*max) && sol->nScelte > bestSol->nScelte)){
        (*max)=punteggio;
        bestSol->nScelte=sol->nScelte;
        for(j=0; j<sol->nScelte; j++)
            bestSol->scelte[j]=sol->scelte[j];
    }

    if(pos>=w.nParole){
        return;
    }

    for(i=start; i<w.nParole; i++){
        len=strlen(w.parole[i].parola);
        p=whereIsInTheMatrix(g, *sol, w.parole[i].parola, len, visited);
        if(POSIZIONEisEmpty(p)==VERO)
            continue;
        punteggio=punteggio+w.parole[i].valore;
        (sol->nScelte)++;
        sol->scelte[pos]=SCELTAcrea(w.parole[i].parola, p.r, p.c, p.dir);
        addWord(visited, g.nr, g.nc, p.r, p.c, p.dir, len);
        solveR(g, w, sol, bestSol, max, visited, punteggio, pos+1, i+1);
        punteggio=punteggio-w.parole[i].valore;
        (sol->nScelte)--;
        deleteWord(visited, g.nr, g.nc, p.r, p.c, p.dir, len);
    }
    return;
}




Posizione whereIsInTheMatrix(Grid g, Sol sol, char *word, int len, int **visited){
    int riga, colonna, i, j, indexP;
    int count;

    for(riga=0; riga<g.nr; riga++){
        for(colonna=0; colonna<g.nc; colonna++){
             if(g.griglia[riga][colonna]==word[0]){
                //ORIZZONTALE;
                indexP=0;
                j=colonna;
                count=0;
                while(j<colonna+len && j<g.nc){
                    if(g.griglia[riga][j]==word[indexP++]){
                        count++;
                        if(visited[riga][j]==OCCUPATO){
                            if(checkSostituzioni(sol, riga, j, 'O')==FALSO)
                                break;
                        }
                        j++;
                    }
                    else{
                        break;
                    }
                }
                if(count==len){
                    return POSIZIONEcrea(riga, colonna, 'O');
                }

                //VERTICALE
                indexP=0;
                i=riga;
                count=0;
                while(i<riga+len && i<g.nr){
                    if(g.griglia[i][colonna]==word[indexP++]){
                        count++;
                        if(visited[i][colonna]==OCCUPATO){
                            if(checkSostituzioni(sol, i, colonna, 'V')==FALSO)
                                break;
                        }
                        i++;
                    }
                    else{
                        break;
                    }
                }
                if(count==len){
                    return POSIZIONEcrea(riga, colonna, 'V');
                }

                //DIAGONALE
                indexP=0;
                i=riga;
                j=colonna;
                count=0;
                while(i<riga+len && j<colonna+len && i<g.nr && j<g.nc){
                    if(g.griglia[i][j]==word[indexP++]){
                        count++;
                        if(visited[i][j]==OCCUPATO){
                            if(checkSostituzioni(sol, i, j, 'D')==FALSO)
                                break;
                        }
                        i++;
                        j++;
                    }
                    else{
                        break;
                    }
                }
                if(count==len){
                    return POSIZIONEcrea(riga, colonna, 'D');
                }
             }
        }
    }
    return POSIZIONEsetNull();
}




void addWord(int **visited, int nr, int nc, int rI, int cI, char direzione, int len){
    int riga, colonna;
    switch(direzione){
       case 'O':
          for(colonna=cI; colonna<cI+len && colonna<nc; colonna++){
             visited[rI][colonna]=OCCUPATO;
          }
          break;
       case 'V':
          for(riga=rI; riga<rI+len && riga<nr; riga++){
             visited[riga][cI]=OCCUPATO;
          }
          break;
       case 'D':
          for(riga=rI, colonna=cI; riga<rI+len && colonna<cI+len && colonna<nc && riga<nr; riga++, colonna++){
             visited[riga][colonna]=OCCUPATO;
          }
          break;
    }
    return;
}




void deleteWord(int **visited, int nr, int nc, int rI, int cI, char direzione, int len){
    int riga, colonna;
    switch(direzione){
       case 'O':
          for(colonna=cI; colonna<cI+len && colonna<nc; colonna++){
             visited[rI][colonna]=EMPTY;
          }
          break;
       case 'V':
          for(riga=rI; riga<rI+len && riga<nr; riga++){
             visited[riga][cI]=EMPTY;
          }
          break;
       case 'D':
          for(riga=rI, colonna=cI; riga<rI+len && colonna<cI+len && colonna<nc && riga<nr; riga++, colonna++){
             visited[riga][colonna]=EMPTY;
          }
          break;
    }
    return;
}




int **malloc2D(int nr, int nc, int value){
    int **mat;
    int i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL){
        exit(EXIT_FAILURE);
    }
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL){
            exit(EXIT_FAILURE);
        }
    }
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            mat[i][j]=value;
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




Boolean checkSostituzioni(Sol proposta, int rI, int cI, char dir){
    int i;
    for(i=0; i<proposta.nScelte; i++){
        if(proposta.scelte[i].p.dir==dir){
            switch(dir){
                case 'O':
                   if(rI==proposta.scelte[i].p.r && cI>=proposta.scelte[i].p.c && cI < proposta.scelte[i].p.c + strlen(proposta.scelte[i].parola)-1){
                      return FALSO;
                   }
                   break;
                case 'V':
                   if(cI==proposta.scelte[i].p.c && rI>=proposta.scelte[i].p.r && rI < proposta.scelte[i].p.r + strlen(proposta.scelte[i].parola)-1){
                      return FALSO;
                   }
                   break;
                case 'D':
                    if((proposta.scelte[i].p.r-proposta.scelte[i].p.c) == (rI-cI)){
                        if(cI>=proposta.scelte[i].p.c && rI>=proposta.scelte[i].p.r){
                            if(cI < proposta.scelte[i].p.c + strlen(proposta.scelte[i].parola)-1 && rI < proposta.scelte[i].p.r + strlen(proposta.scelte[i].parola)-1)
                                return FALSO;
                        }
                   }
                   break;
            }
        }
    }
    return VERO;
}
