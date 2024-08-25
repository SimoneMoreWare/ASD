#include <stdio.h>
#include <stdlib.h>
#include "List.h"


int main()
{
    LIST l;
    l=init();
    int k;

    insertList(l);

    printf("Inserisci k: ");
    scanf("%d",&k);
    f(l,k);
    printList(l);


    return 0;
}
