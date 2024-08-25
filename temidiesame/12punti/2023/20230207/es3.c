#include <stdio.h>
#include <stdlib.h>

void algEr(int *sol,int *stop,int pos,int **M,int N,int m);
void f(int **M,int N);
int check(int *sol,int **M,int N,int m);

int main()
{
    int N;
    int i,j;
    int **M;
    FILE *fp;
    fp=fopen("matrix.txt","r");
    if(fp==NULL)
        return -1;

    printf("Inserisci N: ");
    scanf("%d",&N);

    M=malloc(N*sizeof(int *));
    for(i=0;i<N;i++)
        M[i]=malloc(N*sizeof(int));

    for(i=0;i<N;i++){
        for(j=0;j<N;j++)
            fscanf(fp,"%d",&M[i][j]);
    }

    fclose(fp);

    for(i=0;i<N;i++){
        for(j=0;j<N;j++)
        printf("%d ",M[i][j]);
    printf("\n");
    }

    f(M,N);


    return 0;
}

void f(int **M,int N){

    int *sol=malloc(N*sizeof(int));
    int pos=0;
    int stop=0;
    int m=0;

    algEr(sol,&stop,pos,M,N,m);

    free(sol);
}

void algEr(int *sol,int *stop,int pos,int **M,int N,int m){
    int i;

    if((*stop)==1)return;

    if(pos>=N){
        if((check(sol,M,N,m))==1)
            *stop=1;
    return;
    }


    for(i=0;i<m;i++){
        sol[pos]=i;
        algEr(sol,stop,pos+1,M,N,m);
    }
    sol[pos]=m;
    algEr(sol,stop,pos+1,M,N,m+1);

}

int check(int *sol,int **M,int N,int m){
    int i,j,k,f;
    int found=0;



for(i=0;i<m;i++){
    for(k=0;k<N;k++){
    if(sol[k]==i){
        for(j=k+1;j<N;j++){
            if(sol[j]==i){
                if(M[k][j]==0){
                    found=0;
                    for(f=k+1;f<N;f++){
                        if(sol[f]==i){
                        if(M[k][f]!=0)
                            found=1;
                        }
                    }
                        if(!found)
                            return 0;


                }


            }
        }


    }
    }
}


        for(i=0;i<m;i++){
            printf("{ ");
            for(j=0;j<N;j++){
                if(sol[j]==i)
                    printf("%d ",j);
            }
            printf("}");
        }


    return 1;
}






/*


    for(i=0;i<m;i++){
        for(j=0;j<N;j++)
       for(j=0;j<N;j++){//4 valori
            if(sol[j]==i){//j valore sta nel blocco 0,1 j=1,2,3,4
                for(k=j+1;k<N ;k++){
                    trovata=0;
                    if(sol[k]==i)//se stanno nello stesso blocco devono risp
                        if(M[j][k]==0){
                                for(f=0;f<N && !trovata;f++){
                                    if(sol[f]==i){
                                        if(M[j][f]>0){
                                            if(M[k][f]>0)
                                                trovata=1;
                                        }

                                    }
                                }
                                if(trovata==0)
                                    return 0;
                                //val 1 e val k che è la prossima col pres
                        //basta 1 non c'è flag=1 di nuovo
                        }
                }
            }
        }

    }

    */
