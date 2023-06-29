#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum{VERO, FALSO}Boolean;

int **malloc2D(int nr, int nc);
void free2D(int **mat, int nr);
int *readPopolazione (char *nomeFile, int *dim);
int **readDistanze(char *nomeFile, int dim);
int *readProposta(char *nomeFile, int *dim, int *distMax);
int *readStazioniComune (char *nomeFile, int dim);
Boolean verifica(int *proposta, int dimProp, int **distanze, int N, int distMax);
Boolean solveR(int **distanze, int N, int distMax, int *sol, int dimInsieme, int pos, int start);
void solveFunzioneObiettivo1(int **distanze, int N, int distMax);
int distPesata(int **distanze, int *pop, int N, int *sol, int dimSol);
void solve2R(int **distanze, int N, int numStaz, int *stazComune, int *pop, int *sol, int *bestSol, int *min, int pos, int start);
void solveFunzioneObiettivo2(int **distanze, int N, int numStaz, int *stazComune, int *pop);

int main(){
    int N, *pop, **dist, *proposta, dimProposta, distMax, *stazioniComune, numStaz;

    pop=readPopolazione("popolazione.txt", &N);
    dist=readDistanze("distanze.txt", N);
    proposta=readProposta("proposta.txt", &dimProposta, &distMax);
    stazioniComune=readStazioniComune("stazioniComune.txt", N);

    printf("---PROBLEMA DI VERIFICA:---\n");
    if(verifica(proposta, dimProposta, dist, N, distMax)==VERO)
       printf("Soluzione valida.\n\n");
    else
       printf("Soluzione non valida.\n\n");

    printf("---PROBLEMA DI RICERCA 1:---\n");
    distMax=8;
    solveFunzioneObiettivo1(dist, N, distMax);

    printf("---PROBLEMA DI RICERCA 2:---\n");
    numStaz=2;
    solveFunzioneObiettivo2(dist, N, numStaz, stazioniComune, pop);

    free(pop);
    free2D(dist, N);
    free(proposta);
    free(stazioniComune);
    return 0;
}




int **malloc2D(int nr, int nc){
    int **mat, i;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL)
      exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL)
            exit(EXIT_FAILURE);
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




int *readPopolazione (char *nomeFile, int *dim){
    FILE *f;
    int *pop, i;

    f=fopen(nomeFile, "r");
    if(f==NULL)
      exit(EXIT_FAILURE);
    fscanf(f, "%d", dim);
    pop=(int*)malloc((*dim)*sizeof(int));
    if(pop==NULL)
       exit(EXIT_FAILURE);
    for(i=0; i<(*dim); i++)
       fscanf(f, "%d", &pop[i]);
    fclose(f);
    return pop;
}




int **readDistanze(char *nomeFile, int dim){
    int **dist, i, j;
    FILE *f;

    f=fopen(nomeFile, "r");
    if(f==NULL)
       exit(EXIT_FAILURE);

    dist=malloc2D(dim, dim);
    for(i=0; i<dim; i++)
       for(j=0; j<dim; j++)
           fscanf(f, "%d", &dist[i][j]);
    fclose(f);
    return dist;
}




int *readProposta(char *nomeFile, int *dim, int *distMax){
    int *prop, i;
    FILE *f;
    f=fopen(nomeFile, "r");
    if(f==NULL)
       exit(EXIT_FAILURE);
    prop=(int*)malloc((*dim)*sizeof(int));
    if(prop==NULL)
       exit(EXIT_FAILURE);
    fscanf(f, "%d %d", dim, distMax);
    for(i=0; i<(*dim); i++)
       fscanf(f, "%d", &prop[i]);
    return prop;
}




int *readStazioniComune (char *nomeFile, int dim){
    FILE *f;
    int *stazCom, i;

    f=fopen(nomeFile, "r");
    if(f==NULL)
      exit(EXIT_FAILURE);
    stazCom=(int*)malloc(dim*sizeof(int));
    if(stazCom==NULL)
       exit(EXIT_FAILURE);
    for(i=0; i<dim; i++)
       fscanf(f, "%d", &stazCom[i]);
    fclose(f);
    return stazCom;
}




Boolean verifica(int *proposta, int dimProp, int **distanze, int N, int distMax){
    int i, j, stazione, *distStazione;

    distStazione=(int*)malloc(N*sizeof(int));
    if(distStazione==NULL)
       exit(EXIT_FAILURE);
    for(i=0; i<N; i++)
       distStazione[i]=INT_MAX;

    for(i=0; i<dimProp; i++){
       stazione=proposta[i];
       for(j=0; j<N; j++){
          if(distanze[stazione][j]<distStazione[j])
             distStazione[j]=distanze[stazione][j];
       }
    }
    for(i=0; i<N; i++)
       if(distStazione[i]>distMax)
          return FALSO;
    return VERO;
}




Boolean solveR(int **distanze, int N, int distMax, int *sol, int dimInsieme, int pos, int start){
    int i;
    if(pos>=dimInsieme){
       if(verifica(sol, dimInsieme, distanze, N, distMax)==VERO){
          return VERO;
       }
       return FALSO;
    }
    for(i=start; i<N; i++){
       sol[pos]=i;
       if(solveR(distanze, N, distMax, sol, dimInsieme, pos+1, i+1)==VERO)
          return VERO;
    }
    return FALSO;
}




void solveFunzioneObiettivo1(int **distanze, int N, int distMax){
    int *sol, k, i;

    sol=(int*)malloc(N*sizeof(int));
    if(sol==NULL)
       exit(EXIT_FAILURE);

    for(k=1; k<=N; k++){
       if(solveR(distanze, N, distMax, sol, k, 0, 0)==VERO)
          break;
    }
    printf("distMax: %d - stazMin: %d\n", distMax, k);
    printf("sol: (");
    for(i=0; i<k; i++)
       printf("%d%s", sol[i], (i==(k-1)?")":", "));
    printf("\n\n");
    free(sol);
    return;
}




int distPesata(int **distanze, int *pop, int N, int *sol, int dimSol){
    int *distStazMin, *numStazDistMin, i, stazione, j, somma=0;

    distStazMin=(int*)malloc(N*sizeof(int));
    if(distStazMin==NULL)
       exit(EXIT_FAILURE);
    for(i=0; i<N; i++)
       distStazMin[i]=INT_MAX;
    numStazDistMin=calloc(N, sizeof(int));
    if(numStazDistMin==NULL)
       exit(EXIT_FAILURE);

    for(i=0; i<dimSol; i++){
       stazione=sol[i];
       for(j=0; j<N; j++){
          if(distanze[stazione][j]<distStazMin[j]){
             distStazMin[j]=distanze[stazione][j];
             numStazDistMin[j]=1;
          }
          else if(distanze[stazione][j]==distStazMin[j])
              numStazDistMin[j]++;
       }
    }

    for(i=0; i<N; i++)
       somma=somma+(pop[i]*distStazMin[i]/numStazDistMin[i]);
    return somma;
}




void solve2R(int **distanze, int N, int numStaz, int *stazComune, int *pop, int *sol, int *bestSol, int *min, int pos, int start){
    int i, j, distPes;

    if(pos>=numStaz){
       distPes=distPesata(distanze, pop, N, sol, numStaz);
       if(distPes < (*min)){
          *min=distPes;
          for(j=0; j<numStaz; j++)
             bestSol[j]=sol[j];
       }
       return;
    }
    for(i=start; i<N; i++){
       if(stazComune[i]==0)
          continue;
       sol[pos]=i;
       stazComune[i]--;
       solve2R(distanze, N, numStaz, stazComune, pop, sol, bestSol, min, pos+1, start);
       start++;
       stazComune[i]++;
    }
    return;
}




void solveFunzioneObiettivo2(int **distanze, int N, int numStaz, int *stazComune, int *pop){
    int *sol, *bestSol, min=INT_MAX, i;

    sol=(int*)malloc(numStaz*sizeof(int));
    if(sol==NULL)
       exit(EXIT_FAILURE);
    bestSol=(int*)malloc(numStaz*sizeof(int));
    if(bestSol==NULL)
       exit(EXIT_FAILURE);
    solve2R(distanze, N, numStaz, stazComune, pop, sol, bestSol, &min, 0, 0);
    printf("Best solution:\n");
    printf("numStaz: %d - Minima distanza pesata: %d\n", numStaz, min);
    printf("sol: (");
    for(i=0; i<numStaz; i++)
       printf("%d%s", bestSol[i], (i==(numStaz-1)?")":", "));
    printf("\n");
    free(sol);
    free(bestSol);
    return;
}
