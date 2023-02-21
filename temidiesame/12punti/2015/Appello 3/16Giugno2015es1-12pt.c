#include <stdio.h>
#include <stdlib.h>
#define N 3

void mul(int *v1, int *v2, int n, int **pv);

int main()
{
    int *v, v1[N] = {0,3,2}, v2[N] = {2,4,3},i;

    mul(v1,v2,N,&v);

    for(i=0; i<2*N;i++){
       printf("%d ", v[i]);
    }

    return 0;
}

void mul(int *v1, int *v2, int n, int **pv){
    int i,j,k,res,c=0;//res = risultato della moltiplicazione tra 2 caselle, c = riporto

    *pv = malloc(2*n*sizeof(int));

    for(i=0; i<2*n;i++){
        (*pv)[i] = 0;
    }

    for(i=n-1; i>=0; i--){ //ciclo che scorre il vettore v2
        k = 2*n+i-n;
        for(j=n-1; j>=0; j--){ //ciclo che scorre il vettore v1
            res = v2[i]*v1[j] + (*pv)[k] + c;
            if(res > 10){
                c = (res - res%10)/10;
                res = res%10;
            }else{
                c = 0;
            }
            (*pv)[k] = res;
            k--;
        }
    }
}
