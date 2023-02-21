#include <stdio.h>
#include <stdlib.h>
#define N 10

void printvetmax(int*v, int n);

int main()
{
    int v[N]={1,3,4,0,1,0,9,4,2,0};

    printvetmax(v,N);

    return 0;
}

void printvetmax(int *v, int n)
{
    int i, c=0, cmax=0, j;

    int* v2=malloc(n*sizeof(int));

    for(i=0; i < n; i++)
    {
        if(v[i]!=0) c++;
        else
        {
            if(c > cmax)
                cmax=c;

            i++;
            c=0;
        }
    }

    if(cmax==0)
    {
        printf("gli elementi del vettore sono tutti nulli\n");
        return;
    }

     printf("i sotto vettori di dimensione massima sono:\n\n");
    for(i=0; i < n; i++)
    {
        if(v[i]!=0)
        {
            v2[c]=v[i];
            c++;
        }
        else
            {
                if(c==cmax)
                {
                    for(j=0; j<c; j++)
                     printf("%d", v2[j]);
                     puts("");
                     i++;
                     c=0;
                }
            }
    }
}
