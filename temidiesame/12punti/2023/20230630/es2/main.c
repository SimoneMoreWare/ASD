#include <stdio.h>
#include <stdlib.h>
#include "List.h"

int main()
{

    LIST l;
    l=init();

    insertList(l,1);
    insertList(l,-2);
    insertList(l,3);
    insertList(l,8);
    insertList(l,5);
    insertList(l,6);
    insertList(l,7);
    insertList(l,9);

    printList(l);

    f(l);

    printList(l);

    return 0;
}
