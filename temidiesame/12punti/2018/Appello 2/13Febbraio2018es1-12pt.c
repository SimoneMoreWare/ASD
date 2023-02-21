#include <stdio.h>
#include <stdlib.h>


void printsquare(int** A, int n, int m);


int main()
{

    int**A, i, j, m, n;

    FILE* fl;
    fl=fopen("mat.txt", "r");
    if(fl==NULL) return -1;

    fscanf(fl ,"%d%d",&n,&m);
    A=malloc(n*sizeof(int*));

    for(i=0; i<n; i++)  // lettura matrice da file
    {
        A[i]=malloc(m*sizeof(int));
        for(j=0; j<m; j++)
            fscanf(fl,"%d", &A[i][j]);
    }



    for(i=0; i < n; i++) // stampa matrice
    {
        for(j=0; j < m; j++)
            printf("%d\t", A[i][j]);
        printf("\n");
    }
   printf("\n\n");

    printsquare(A, n, m); // funzione che stampa le sottomatrici quadrate
    return 0;
}

void printsquare(int** A, int n, int m)
{
    int i, j, k, c, l;


    if(n>m) c=m;
    else c=n;


    for(   ; c>0; c--)
    for(l=0; l <= n-c ; l++)
    for(k=0; k <= m -c; k++ )
    {
        for(i=0 +l; i< c +l; i++)
        {
            for(j=0 + k; j< c +k ;j++)
            {
                printf("%d\t", A[i][j]);
            }
            printf("\n");
        }

        puts("-----------------------------------------------");
    }

    return;
}
