/*
Sigla lunghezza N
per ogni posizione sigla[i] vi è un carattere che appartiene all'insieme set[j]

cardinalità massima set[j] 10

N
set[0]
set[1]
...
set[N-1]

creo una matrice di char NxN e la riempio di \0
inizializzo
A \0 \0
X Y \0
1 2 3

per generare tuttue possibili sigle uso il principio di moltiplicazione

*/

void initmatric(int N, char **matr){
    int i,j;
    matr=(char **) malloc(N*sizeof(char *));
    for(i=0;i<N;i++) matr[i]=(char *) malloc(MAXNCARDINALITA*sizeof(char));
    for(i=0;i<N;i++) for(j=0;j<MAXNCARDINALITA;j++) matr[i][j]='\0';
}

//void loadmatrix(...) ... non importa

void principiodimoltiplicazione(int pos,char **val, char *sol,int n,FILE *fout){
    int i;
    if(pos>n){
        for(i=0;i<n;i++) fprintf(fout,"%c",sol[i]);
        fprintf(fout,"\n");
        return;
    }
    for(i=0;val[pos][i]!='\0';i++){
    	sol[pos]=matr[pos][i];
        principiodimoltiplicazione(pos+1,val,sol,n,fout);
    }
}

