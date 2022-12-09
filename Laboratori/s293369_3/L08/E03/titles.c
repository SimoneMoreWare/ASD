//
// Created by simone on 08/12/22.
//

#include "titles.h"

struct{
    char name[MAXC];
    datetime data;
    BST quotazioni;
}title;

typedef struct node *link;
struct node { Title val; link next; };
struct listtitle { link head; int N; };

void readfile(FILE *fp){
    BST bstq = NULL;
    readbst(bstq,fp);
}

