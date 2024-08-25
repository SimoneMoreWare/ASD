#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main()
{
    LIST l;
    int i;
    l=init();

    for(i=0;i<11;i++)
    insertList(l,i);

    printList(l);
    f(l,3,5);
    printList(l);


    return 0;
}
