#include <stdio.h>
#include <stdlib.h>
void f(int M[4][4],int N);
void algoritmodiEr(int pos,int m,int mblocchimax,int M[4][4],int N,int *sol,int *stop,int *best);
int check(int m,int N,int *sol,int M[4][4]);
int main(){
    int M[4][4]= {
            {1,1,0,1},
            {1,1,1,0},
            {0,1,1,1},
            {1,0,1,1}
    };
    int N=4;
    f(M,N);
    return 0;
}

void f(int M[4][4],int N){
    int pos=0;
    int *sol = (int *) malloc(N*sizeof(int));
    int m=0;
    int stop = 0;
    int i,j;
    int *best = (int *) malloc(N*sizeof(int));
    for(i=1;i<=N && stop==0;i++) algoritmodiEr(pos,m,i,M,N,sol,&stop,best);//itero da 1 fino a mblocchi,
    //appena trovo una soluzione compatibile mi fermo, se trovo la soluzione sarà sicuramente quella con mi
    // numero di blocchi
    int mblocchi=i-1;
    if(stop==0){
        printf("Soluzione non trovata");
    }else{
        //stampi vettore best , il numero di blocchi lo sai perchè conosci i
        printf("Blocchi %d\n",mblocchi);
        for(i=0;i<mblocchi;i++){
            printf("{");
            for(j=0;j<N;j++){
                if(best[j]==i) printf("%d ",j);
            }
            printf("} ");
        }
    }
    free(sol);
}

void algoritmodiEr(int pos,int m,int mblocchimax,int M[4][4],int N,int *sol,int *stop,int *best){
    int i;
    if((*stop)==1) return;
    if(pos>=N){
        if(m==mblocchimax){
            if(check(m,N,sol,M)){
                (*stop)=1;
                for(i=0;i<N;i++) best[i]=sol[i];
            }
        }
        return;
    }
    for(i=0;i<m;i++){
        sol[pos]=i;
        algoritmodiEr(pos+1,m,mblocchimax,M,N,sol,stop,best);
    }
    sol[pos]=m;
    algoritmodiEr(pos+1,m+1,mblocchimax,M,N,sol,stop,best);
}

int check(int m,int N,int *sol,int M[4][4]) {
    int i, j;
    int t, l;
    int cnt;
    int flag;
    for (i = 0; i < m; i++) {
        for (j = 0; j < N; j++) {
            cnt=0;
                for (t = j+1; t < N; t++) {
                    if (sol[j] == i && sol[t] == i) {
                        flag = 0;
                        if (M[j][t] == 0) {
                            for (l = 0; l < N && flag==0 ; l++) {
                               if (sol[l] == i && l != t) {
                                  if (M[i][l] != 0) {
                                       cnt++;
                                       flag=1;
                                    }
                                }
                            }
                            if(flag==0) return 0;
                            if(cnt>1) return 0;
                        }
                    }
                }


        }

    }
    return 1;
}
