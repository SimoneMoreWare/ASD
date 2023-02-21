#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"



int main()
{
    int fl;

    FILE* fl1;
    FILE* fl2;
    BST a, b;
    a=BSTinit();
    b=BSTinit();

    fl1=fopen("bst1.txt" , "r");
    if(fl1==NULL) return -1;

    fl2=fopen("bst2.txt","r");
    if(fl2==NULL) return -2;

    bstreadPreorder(fl1, a); // lettura alberi da file
    bstreadPreorder(fl2, b);

    fl=subtree( getroot(a), getroot(b));

    printf("\n%d\n",fl);


    return 0;
}
