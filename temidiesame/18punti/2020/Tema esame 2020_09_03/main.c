#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "schema.h"

typedef enum{VERO, FALSO}Boolean;

int** leggiMappa(FILE *fin, int *R, int *C);
int **malloc2D(int nr, int nc);
void free2D(int **mat, int nr);
int verifica(char *fn, int **mappa);
void verificaR(int **griglia, int nr, int nc, int areaRegione, int *count, int **visited, int riga, int colonna);
void solve(int **m, int R, int C);
void solveR(int **m, int R, int C, int **bestSol, int *min, Boolean *trovato, int *numbers, int pos);
Boolean checkSol(int **sol, int nr, int nc);
int differentNumbers(int *numbers, int dim);

int main()
{
    FILE *f;
    int **mappa, nr, nc;

    f=fopen("griglia.txt", "r");
    if(f==NULL) exit(EXIT_FAILURE);

    mappa=leggiMappa(f, &nr, &nc);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(verifica("proposta.txt", mappa)==VERO){
        printf("Soluzione valida.\n");
    }
    else{
        printf("Soluzione non valida.\n");
    }

    printf("\n---PROBLEMA DI RICERCA:---\n");
    solve(mappa, nr, nc);
    free2D(mappa, nr);
    return 0;
}




int** leggiMappa(FILE *fin, int *R, int *C){
       Schema s=SCHEMAread(fin);
       *R=s.nr;
       *C=s.nc;
       return s.mat;
}




int **malloc2D(int nr, int nc){
    int **mat, i;
    mat=malloc(nr*sizeof(int**));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    return mat;
}




int verifica(char *fn, int **mappa){
       FILE *f;
       Schema s;
       int i, j, count;
       int **visited;

       f=fopen(fn, "r");
       if(f==NULL) exit(EXIT_FAILURE);
       s=SCHEMAread(f);

       for(i=0; i<s.nr; i++){
          for(j=0; j<s.nc && mappa[i][j]!=0; j++){
             if(mappa[i][j]!=s.mat[i][j]){
                return FALSO;
             }
          }
       }
       visited=malloc2D(s.nr, s.nc);
       for(i=0; i<s.nr; i++)
          for(j=0; j<s.nc; j++)
             visited[i][j]=0;

       for(i=0; i<s.nr; i++){
          for(j=0; j<s.nc; j++){
             count=0;
             if(visited[i][j]==0){
                verificaR(s.mat, s.nr, s.nc, s.mat[i][j], &count, visited, i, j);
                if(count!=s.mat[i][j])
                    return FALSO;
             }
          }
       }
       return VERO;
}




void verificaR(int **griglia, int nr, int nc, int areaRegione, int *count, int **visited, int riga, int colonna){
	if(riga<0 || riga>=nr || colonna<0 || colonna>=nc){
             return;
      }
      if(griglia[riga][colonna]!=areaRegione){
         return;
      }
      if(visited[riga][colonna]==0){
         (*count)++;
         visited[riga][colonna]=1;
         verificaR(griglia, nr, nc, areaRegione, count, visited, riga+1, colonna);
         verificaR(griglia, nr, nc, areaRegione, count, visited, riga-1, colonna);
         verificaR(griglia, nr, nc, areaRegione, count, visited, riga, colonna+1);
         verificaR(griglia, nr, nc, areaRegione, count, visited, riga, colonna-1);
      }
      return;
}




void free2D(int **mat, int nr){
    int i;
    if(mat!=NULL){
        for(i=0; i<nr; i++){
            free(mat[i]);
        }
        free(mat);
    }
    return;
}




void solve(int **m, int R, int C){
       int *numbers, i, min=INT_MAX, j;
       int **bestSol;
       Boolean trovato=FALSO;

       numbers=(int*)calloc(9, sizeof(int));
       if(numbers==NULL) exit(EXIT_FAILURE);

       bestSol=malloc2D(R, C);

       solveR(m, R, C, bestSol, &min, &trovato, numbers, 0);

       if(trovato==VERO){
          printf("Best Solution:\n");
          for(i=0; i<R; i++){
              for(j=0; j<C; j++)
                  printf("%d ", bestSol[i][j]);
              printf("\n");
          }
       }
       else{
          printf("Soluzione non trovata.\n");
       }
       free2D(bestSol, R);
       return;
}




void solveR(int **m, int R, int C, int **bestSol, int *min, Boolean *trovato, int *numbers, int pos){
      int r, c, numero, diff, i, j;

	diff=differentNumbers(numbers, 9);
	if(diff>(*min)){
        return;
    }
	if(pos>=(R*C)){
        if(checkSol(m, R, C)==VERO && diff<(*min)){
            *trovato = VERO;
            *min=diff;
            for(i=0; i<R; i++)
                for(j=0; j<C; j++)
                    bestSol[i][j]=m[i][j];
        }
        return;
    }
    r=pos/C;
    c=pos%C;
    if(m[r][c]!=0){
         numbers[m[r][c]-1]++;
         solveR(m, R, C, bestSol, min, trovato, numbers, pos+1);
         return;
    }
    for(numero=9; numero>=1; numero--){
         m[r][c]=numero;
         numbers[numero-1]++;
         solveR(m, R, C, bestSol, min, trovato, numbers, pos+1);
         numbers[numero-1]--;
         m[r][c]=0;
    }
    return;
}




int differentNumbers(int *numbers, int dim){
      int i, count=0;
      for(i=0; i<dim; i++){
          if(numbers[i]!=0)
              count++;
      }
      return count;
}




Boolean checkSol(int **sol, int nr, int nc){
      int **visited, i, j, count;

      visited=malloc2D(nr, nc);
      for(i=0; i<nr; i++){
          for(j=0; j<nc; j++){
             visited[i][j]=0;
          }
      }

      for(i=0; i<nr; i++){
         for(j=0; j<nc; j++){
            count=0;
            if(visited[i][j]==0){
               verificaR(sol, nr, nc, sol[i][j], &count, visited, i, j);
               if(count!=sol[i][j]){
                   return FALSO;
               }
            }
         }
      }
      return VERO;
}
