/*
 * dato un grafo non orientato G
 * di N vertici
 *  vertici indentificati nell'intervallo 0...N-1
 *  E archi
 *  indentificati come coppie di vertici
 *
 *  file
 *  prima riga N vertici E archi
 *  succesive E righe archi u-v
 *
 *  vertex cover
 *  sottonsieme W dei vertici
 *  tali che tutti gli archi E abbiano almeno uno dei 2 vertici su cui incidono W
 *
 *  salvare grafo in opportune strutture dati
 *
 *  elencare vertex cortex
 *
 *
il vertex cover mira a trovare quei vertici che "vedono" la totalità degli archi. in questo caso l'1"vede" l'arco 1-0, 1-2 e 1-3 mentre il 2 vede l'arco 2-0 e 2-1 (ridondante)
così facendo sono coperti tutti gli archi
Per ogni arco devi controllare che nella soluzione ci siano almeno uno tra il vertice di partenza e quello di arrivo
Definizione di vertex cover è che ogni arco deve avere almeno uno dei due vertici estremità nel set di vertici scelto

 Il vertex cover è un sottoinsieme di vertici che comprende tutti gli archi.
L'insieme 0,2,3 contiene tutti gli archi e quindi è connesso.
0,2 non contiene l'arco (1,3) perciò non è connesso.

 https://en.wikipedia.org/wiki/Vertex_cover
 */

#include <stdio.h>
#include <stdlib.h>

#define filename "../brani.txt"

void leggifile();
int **malloc2dr(int N,int E,FILE *fpin);
void dealloca(int **matrixgraph, int N);
int powerset(int pos,int **matrixgraph,int *sol,int *tmp,int N,int cnt);
void azzerratmp(int **tmp,int N);
int checksolution(int *tmp,int N, int *sol, int cnt);

int main(){
    leggifile();
    return 0;
}

void leggifile(){
    FILE *fpin;
    int N,E;
    int pos=0;
    int *sol;
    int *tmp;
    int cnt=0;
    int **matrixgraph; //matrice di adiacenza

    fpin=fopen(filename,"r");

    if(fpin!=NULL){

        fscanf(fpin,"%d",&N);
        fscanf(fpin,"%d",&E);

        matrixgraph= malloc2dr(N,E,fpin);
        sol=(int *) malloc(N*sizeof(int));
        tmp=(int *) calloc(N,sizeof(int));

        cnt=powerset(pos,matrixgraph,sol,tmp,N,cnt);
        printf("%d ",cnt);

        dealloca(matrixgraph,N);

    }else{
        printf("Errore file");
    }
}

int **malloc2dr(int N,int E, FILE *fpin){

    int **creatematrix;
    int i;
    int u,v;

    creatematrix=(int **) calloc(N,sizeof(int *)); //creo vettore "verticale" di puntatore, ogni casella punterà a un vettore
    for(i=0;i<N;i++) {
        creatematrix[i] = (int *) calloc(N ,sizeof(int));//per ogni casella del vettore verticale preparo lo spazio di memoria per il vettore
    }

    for (i = 0; i < E; i++) {
        fscanf(fpin,"%d",&u); // inserisco valore
        fscanf(fpin,"%d",&v); // inserisco valore
        creatematrix[u][v]=1;
        creatematrix[v][u]=1;
    }

    return creatematrix; //ritorno doppio puntatore (aka matrice) alla funzione chiamante
}

int powerset(int pos,int **matrixgraph,int *sol,int *tmp,int N,int cnt){
    int i,j;
    if (pos >= N) {
        for (j=0; j<N; j++) {
            if (sol[j] != 0){
                for (i = 0; i < N; i++) if(matrixgraph[j][i]==1) tmp[i]=1;
            }
        }
        cnt=checksolution(tmp,N,sol,cnt);
        azzerratmp(&tmp,N);
        return cnt;
    }
    sol[pos] = 0;
    cnt = powerset(pos+1, matrixgraph, sol,tmp, N, cnt);
    sol[pos] = 1;
    cnt = powerset(pos+1, matrixgraph, sol,tmp, N, cnt);
    return cnt;
}

int checksolution(int *tmp,int N, int *sol, int cnt){
    int i,j;
    int flag=1;
    //int m=N/2+N%2;
    for(i=0;i<N && flag==1;i++) if(tmp[i]!=1) flag=0;

    if(flag==1){
        for (j=0; j<N; j++){
            if (sol[j]!=0){
                printf("%d ", j);
            }
        }
        printf("\n");
        return cnt+1;
    }
    return cnt;
}
void azzerratmp(int **tmp,int N){
    for(int i=0;i<N;i++) (*tmp)[i]=0;
}

void dealloca(int ** matrixgraph, int N){
    for(int i=0;i<N;i++) free(matrixgraph[i]);
    free(matrixgraph);
}
