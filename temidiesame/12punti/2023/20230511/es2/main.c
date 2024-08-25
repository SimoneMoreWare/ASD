#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main()
{
    LIST l;
    int *interi;
    int N;
    int i;

    printf("Inserisci N: ");
    scanf("%d",&N);
    interi=malloc(N*sizeof(int));
    for(i=0;i<N;i++)
        scanf("%d",&interi[i]);

    l=init();
    l=insertR(l,interi,N);
    printL(l);
    f(l);
    printL(l);




    return 0;
}
