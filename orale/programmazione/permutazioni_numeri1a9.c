/*
 * Dati i numeri da uno a nove,
 * trovare tutte le permutazioni per cui
 * n0 = pari, n1 = dispari e n2 = pari
 * e tali per cui n0>n1>n2
 */

//permutazioni semplici

#include <stdio.h>
#include <stdlib.h>

void wrapper(int val[9],int N);
void permutazionisemplici(int val[9],int N,int pos,int *mark,int *sol);

int main(){
    int val[] = {1,2,3,4,5,6,7,8,9};
    int N=9;
    wrapper(val,N);
    return 0;
}

void wrapper(int val[9],int N){
    int *sol=(int *) malloc(N*sizeof(int));
    int *mark = (int *) calloc(N,sizeof(int));
    int pos=0;
    permutazionisemplici(val,N,pos,mark,sol);
    free(sol);
    free(mark);
}

void permutazionisemplici(int val[9],int N,int pos,int *mark,int *sol){

    int i;
    if(pos>=N){
        if(val[sol[0]]>val[sol[1]] && val[sol[1]]>val[sol[2]]){
            for(i=0;i<N;i++){
                printf("%d ",val[sol[i]]);
            }
            printf("\n");
        }
        return;
    }

    for(i=0;i<N;i++){
        if(mark[i]==0){
            mark[i]++;
            if(pos==0 && val[i]>=3 && val[i]%2==0){
                sol[pos] = i;
                permutazionisemplici(val, N, pos + 1, mark, sol);
            }else if(pos==1 && val[i]>=2 && val[i]%2!=0){
                sol[pos]=i;
                permutazionisemplici(val,N,pos+1,mark,sol);
            }else if(pos==2 && val[i]>=1 && val[i]%2==0){
                sol[pos]=i;
                permutazionisemplici(val,N,pos+1,mark,sol);
            }else if(pos>2){
                sol[pos]=i;
                permutazionisemplici(val,N,pos+1,mark,sol);
            }
            mark[i]--;
        }
    }
}
