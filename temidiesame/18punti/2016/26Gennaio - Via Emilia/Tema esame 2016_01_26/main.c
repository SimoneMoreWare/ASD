#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "citta.h"

Citta * leggiFile(char *nomeFile, int *dim);
int **calcolaDistanze(Citta *citta, int dim);
int **malloc2D(int nr, int nc);
int SommaDistanze(Citta *citta, int **distanze, int dim, int *cittaATO, int k);
int getDistanzaMinATO(int indexCitta, int **distanze, int *cittaATO, int k);
void solve(Citta *citta, int dim, int **distanze, int k);
void solveR(Citta *citta, int dim, int **distanze, int *sol, int *bestSol, int k, int *min, int start, int pos);
int *leggiProposta(char *nomeFile, Citta *citta, int dim, int k);
int getIndexCitta(Citta *citta, int dim, Citta c);
void verifica(Citta *citta, int dim, int **distanze, int *proposta1, int *proposta2, int k);
void free2D(int **mat, int nr);

int main()
{
    Citta *citta;
    int dim, k=4;
    int **distanze, *proposta1, *proposta2;

    citta=leggiFile("citta.txt", &dim);
    distanze=calcolaDistanze(citta, dim);

    printf("---PROBLEMA DI VERIFICA---\n");
    proposta1=leggiProposta("proposta1.txt", citta, dim, k);
    proposta2=leggiProposta("proposta2.txt", citta, dim, k);
    verifica(citta, dim, distanze, proposta1, proposta2, k);

    printf("\n");
    printf("---PROBLEMA DI RICERCA---\n");
    solve(citta, dim, distanze, k);

    free(citta);
    free2D(distanze, dim);
    free(proposta1);
    free(proposta2);
    return 0;
}




Citta *leggiFile(char *nomeFile, int *dim){
    FILE *f;
    int i;
    Citta *citta;
    f=fopen(nomeFile, "r");
    if(f==NULL) exit(EXIT_FAILURE);
    citta=(Citta*)malloc((*dim)*sizeof(Citta));
    if(citta==NULL) exit(EXIT_FAILURE);
    fscanf(f, "%d", dim);
    for(i=0; i<(*dim); i++)
       citta[i]=CITTAread(f);
    return citta;
}




int **calcolaDistanze(Citta *citta, int dim){
   int **mat, i, j;
   mat=malloc2D(dim, dim);
   for(i=0; i<dim; i++){
      for(j=0; j<dim; j++){
         mat[i][j]=abs(citta[i].distanzaInizio-citta[j].distanzaInizio);
      }
   }
   return mat;
}


int **malloc2D(int nr, int nc){
    int **mat, i;
    mat=(int**)malloc(nr*sizeof(int*));
    if(mat==NULL) exit(EXIT_FAILURE);
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
        if(mat[i]==NULL) exit(EXIT_FAILURE);
    }
    return mat;
}




int SommaDistanze(Citta *citta, int **distanze, int dim, int *cittaATO, int k){
   int SD=0, i;
   for(i=0; i<dim; i++){
      SD+=citta[i].abitanti * getDistanzaMinATO(i, distanze, cittaATO, k);
   }
   return SD;
}


int getDistanzaMinATO(int indexCitta, int **distanze, int *cittaATO, int k){
    int i, min=INT_MAX;
    for(i=0; i<k; i++){
       if(indexCitta!=cittaATO[i] && distanze[indexCitta][cittaATO[i]]<min){
          min=distanze[indexCitta][cittaATO[i]];
       }
    }
    return min;
}




void solveR(Citta *citta, int dim, int **distanze, int *sol, int *bestSol, int k, int *min, int start, int pos){
   int i, SD, j;
   if(pos>=k){
      SD=SommaDistanze(citta, distanze, dim, sol, k);
      if(SD<(*min)){
         (*min)=SD;
         for(j=0; j<k; j++)
            bestSol[j]=sol[j];
      }
      return;
   }
   for(i=start; i<dim; i++){
      sol[pos]=i;
      solveR(citta, dim, distanze, sol, bestSol, k, min, i+1, pos+1);
   }
   return;
}


void solve(Citta *citta, int dim, int **distanze, int k){
   int *sol, *bestSol, min=INT_MAX, i;
   sol=(int*)malloc(k*sizeof(int));
   bestSol=(int *)malloc(k*sizeof(int));
   if(sol ==NULL || bestSol==NULL) exit(EXIT_FAILURE);
   solveR(citta, dim, distanze, sol, bestSol, k, &min, 0, 0);
   printf("Best Solution:\n");
   printf("SD: %d\n", min);
   printf("Citta':\n");
   for(i=0; i<k; i++){
      printf("\t-");
      CITTAprint(citta[bestSol[i]], stdout);
   }
   free(sol);
   free(bestSol);
   return;
}




int getIndexCitta(Citta *citta, int dim, Citta c){
   int i;
   for(i=0; i<dim; i++)
      if(CITTAcompare(citta[i], c)==UGUALE)
         return i;
   return -1;
}


int *leggiProposta(char *nomeFile, Citta *citta, int dim, int k){
   FILE *f;
   int i, *proposta;
   f=fopen(nomeFile, "r");
   Citta c;
   if(f==NULL) exit(EXIT_FAILURE);
   proposta=(int*)malloc(k*sizeof(int));
   if(proposta==NULL) exit(EXIT_FAILURE);
   for(i=0; i<k; i++){
      c=CITTAread(f);
      proposta[i]=getIndexCitta(citta, dim, c);
   }
   return proposta;
}




void verifica(Citta *citta, int dim, int **distanze, int *proposta1, int *proposta2, int k){
   int SD1, SD2, i;
   SD1=SommaDistanze(citta, distanze, dim, proposta1, k);
   SD2=SommaDistanze(citta, distanze, dim, proposta2, k);
   printf("Tra le due proposte, la soluzione migliore e' ");
   if(SD1<SD2){
      printf("quella presente nel file 'proposta1.txt', ovvero:\n");
      printf("SD: %d\n", SD1);
      printf("Citta':\n");
      for(i=0; i<k; i++){
         printf("\t-");
         CITTAprint(citta[proposta1[i]], stdout);
      }
      return;
    }
    printf("quella presente nel file 'proposta2.txt', ovvero:\n");
    printf("SD: %d\n", SD2);
    printf("Citta':\n");
    for(i=0; i<k; i++){
       printf("\t-");
       CITTAprint(citta[proposta2[i]], stdout);
    }
    return;
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
}
