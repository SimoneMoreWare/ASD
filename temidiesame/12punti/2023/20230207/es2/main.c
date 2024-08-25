#include <stdio.h>
#include <stdlib.h>
#include "T.h"

int main()
{
    T t;
    int lenght;
    t=init();

    t=init();
    initTreeNode(t);

    lenght=f(t);
    printf("La lunghezza massima e: %d\n",lenght);


    return 0;
}
