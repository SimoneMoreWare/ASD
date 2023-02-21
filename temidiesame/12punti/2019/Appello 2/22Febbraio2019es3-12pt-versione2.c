#include <stdio.h>
#include <stdlib.h>
#define Q 9

void minMaxRecursive(int pos, int *V, int *sol, int N, int *subSeq, int *maxLength);
void minMaxWrapper(int *V, int N);
void checkSol(int *sol, int *maxLength, int *subSeq, int *V,int N);

int main()
{
    int V[Q] = {8, 9, 6, 4, 5, 7, 3, 2, 4};

    minMaxWrapper(V,Q);

    return 0;
}
void minMaxRecursive(int pos, int *V, int *sol, int N, int *subSeq, int *maxLength){
    if(pos == N){
        checkSol(sol,maxLength,subSeq,V,N);
        return;
    }

    sol[pos] = 0;
    minMaxRecursive(pos+1, V, sol,N,subSeq,maxLength);
    sol[pos] = 1;
    minMaxRecursive(pos+1, V, sol,N,subSeq,maxLength);

    return;
}

void minMaxWrapper(int *V, int N){
    int *sol, *subSeq, maxLength = 0,i;

    sol = malloc(N*sizeof(int));
    subSeq = malloc(N*sizeof(int));

    minMaxRecursive(0,V,sol,N,subSeq,&maxLength);

    printf("MinMax subsequence: ");
    for(i=0;i<N&&subSeq[i]!=-1;i++){
        printf("%d",subSeq[i]);
    }
    printf(" - Length: %d", maxLength);
    return;
}

void checkSol(int *sol, int *maxLength, int *subSeq, int *V,int N){
    int ok = 1, i=1, count = 0, pos = 0;

    for(i=0;i<N;i++){
        subSeq[i] = -1;
        if(sol[i]==1)
            subSeq[pos++]=V[i];
    }

    for(i=0; i<N && ok && subSeq[i]!=-1;i++){
        if(i%2==0){
            if(i+1<N){
                if(subSeq[i]<subSeq[i+1]){
                    count++;
                }else{
                    ok = 0;
                }
            }
        }else{
            if(i+1<N){
                if(subSeq[i]>subSeq[i+1]){
                    count++;
                }else{
                    ok = 0;
                }
            }
        }
    }
    if(ok){
        if(count>*maxLength){
            *maxLength = count;
        }
    }
    return;
}
