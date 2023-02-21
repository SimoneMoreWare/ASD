#include <stdio.h>
#include <stdlib.h>

void wrapper(int M[4][4],int N);
void algoritmoER(int N,int m,int pos,int *sol,int M[4][4],int *stop);
void controlla(int M[4][4],int *sol,int m,int N,int **stop);

/*
 * ho utilizzato l'algoritmo di Er -> per studiarlo vai qui https://geode-rat-694.notion.site/Calcolo-combinatorio-4d131954437a4856b76abe65cfb31e58
 *
 * Per quanto riguarda l’approccio alla ricerca della soluzione, se si decide di guidare la cardinalit`a della
 * soluzione, conviene seguire un approccio fondato su cardinalit`a target crescenti poich ́e stiamo cercando un minimo:
 * dal caso migliore in cui si pu`o usare un singolo gruppo (tutti amici con tutti) al caso peggiore in cui `e
 * necessario avere tanti gruppi quante sono le persone (ogni persona `e amica solo con se stessa).
 * per questo si usa una variabile stop, appena trovo una soluzione cambio il valore di stop e non procedo piu con la
 * ricorsione
 *
 * da implementare
 * E possibile tagliare rami di ricorsione evitando di includere una persona in un gruppo `gia parzialmente formato 
 * se questa aggiunta facesse fallire la condizione di “mutua amicizia” per almeno una coppia di amici nel gruppo. 
 * Allo stesso modo, `e possibile tagliare rami di ricorsione tali per cui la cardinalit`a della soluzione corrente sia
   peggiore rispetto al valore migliore noto in un dato momento.
 */

int main(){
    int M[4][4] = {
            {1,1,0,1},
            {1,1,0,1},
            {0,0,1,0},
            {1,1,0,1}
    };
    int N=4;
    wrapper(M,N);
    return 0;
}

void wrapper(int M[4][4],int N){
    int *sol = (int *) malloc(N*sizeof(int));
    int m=0;
    int pos=0;
    int stop=0;
    algoritmoER(N,m,pos,sol,M,&stop);//uso variabile stop in modo tale che quando trovo una soluzione valida mi fermo, in quanto
    free(sol);
}

void algoritmoER(int N,int m,int pos,int *sol,int M[4][4],int *stop){
    int i;

    if(*(stop)==1) return;

    if(pos>=N){
        controlla(M,sol,m,N,&(stop));
        return;
    }

    for(i=0;i<m;i++){
            sol[pos]=i;
            algoritmoER(N,m,pos+1,sol,M,stop);
    }
    sol[pos]=m;
    algoritmoER(N,m+1,pos+1,sol,M,stop);
}

void controlla(int M[4][4],int *sol,int m,int N,int **stop) {
    int i, j,k;
    int flag = 1;
    for (i = 0; i < m; i++) {
        for (j = 0; j < N; j++) {
            if (sol[j] == i){
                for (k = j + 1; k < N; k++){
                    if (sol[k] == i)  if (M[j][k] == 0) flag = 0;
                }
            }
        }
    }
    if (flag == 1) {
        (**stop) = 1;
        for (i = 0; i < m; i++) {
            printf("{ ");
            for (j = 0; j < N; j++) if (sol[j] == i) printf("%d ", j);
            printf("}  ");
        }
    }
}
