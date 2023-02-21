#include <stdio.h>
#include <stdlib.h>

void porto(int* navi, int n, int k, int A, int m);
void disps(int pos, int* val, int* sol, int* solmin, int* smin, int n, int k, int* mark, int A, int m);
void portmin(int* sol, int* solmin, int* smin, int k, int A, int m);
void printsol(int* solmin, int k, int smin);


int main()
{
    int k=7, m=4, A=10,n, navi[7] ={8,3,5,2,5,2,9,7};

    n=k;

    porto(navi, n, k, A, m);

    return 0;
}

void porto(int* navi, int n, int k, int A, int m)
{
    int i, smin=-1;

    int* solmin= malloc(k*sizeof(int));
    int* sol= malloc(k*sizeof(int));
    int* mark= malloc(n*sizeof(int));
    for(i=0; i<n; i++)
            mark[i]=1;

    disps(0, navi, sol, solmin, &smin, n, k, mark, A, m);

    printsol(solmin, k, smin);

}

void disps(int pos, int* val, int* sol, int* solmin, int* smin, int n, int k, int* mark, int A, int m)
{
    int i;

    if(pos >= k)
    {
        portmin(sol, solmin, smin, k, A, m);
        return;
    }

    for(i=0; i<n; i++)
        if(mark[i]!=0)
        {
            sol[pos]=val[i];
            mark[i]=0;

            disps(pos+1, val, sol, solmin, smin, n, k, mark, A, m);
            mark[i]=1;

        }

        return;
}


void portmin(int* sol, int* solmin, int*smin, int k, int A, int m)
{
    int count=1 , i, j, s=0;

    for(i=0; i<k; i++)
    {
        s= s +sol[i];
        if(s > A)
        {
            count++;
            s=s-sol[i];
            i--;
            s=0;
        }
    }

    count= (count+1)/2;
    if(count <= m)
        if(count < *smin || *smin==-1)
        {
            *smin=count;
            for(j=0; j<k; j++)
            solmin[j]=sol[j];

        }
        return ;
}

void printsol(int* solmin, int k, int smin)
{
    int i;

    if(smin >= 0)
    {
       printf("\nmoli utilizzati %d\n", smin);
       printf("la disposizione delle navi e' la seguente:\n");
       for(i=0; i<k; i++)
         printf("%d\n",solmin[i]);

    }
    else
        printf("\nnumero di moli insufficenti\n");

}
