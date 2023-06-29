#include <stdio.h>
#include <stdlib.h>
#include "piatti.h"
#include "BST.h"

BST generaMenu(Piatti p, int P);
void combSemp(Piatti p, int nPiatti, int *piattiBis, BST menus, int *sol, int P, float costo, int pos, int start);

int main()
{
    Piatti p;
    int P=5;
    FILE *f;
    BST menus;

    f=fopen("piatti.txt", "r");
    if(f==NULL)
        exit(EXIT_FAILURE);

    p=PIATTIread(f);

    menus=generaMenu(p, P);

    BSTprint(menus, p, fopen("menu.txt", "w"));
    return 0;
}




BST generaMenu(Piatti p, int P){
    int *piattiBis, *sol, nPiatti, i, piatto=0;
    float costo=0;
    BST menus=BSTinit();

    nPiatti=PIATTIsize(p);

    piattiBis=(int*)malloc(2*nPiatti* sizeof(int));
    if(piattiBis==NULL)
       exit(EXIT_FAILURE);

    for(i=0; i<2*nPiatti; i=i+2){
        piattiBis[i]=piatto;
        piattiBis[i+1]=piatto;
        piatto++;
    }

    sol=(int*)malloc(P*sizeof(int));
    if(sol==NULL)
       exit(EXIT_FAILURE);

    combSemp(p, 2*nPiatti, piattiBis, menus, sol, P, costo, 0, 0);
    return menus;
}




void combSemp(Piatti p, int nPiatti, int *piattiBis, BST menus, int *sol, int P, float costo, int pos, int start){
    int i;
    Piatto piatto;
    if(pos>=P){
       BSTinsertLeaf(menus, MENUcreate(P, sol, costo));
       return;
    }
    for(i=start; i<nPiatti; i++){
       piatto=PIATTIgetPiatto(p, piattiBis[i]);
       sol[pos]=piattiBis[i];
       costo=costo+piatto.costo;
       combSemp(p, nPiatti, piattiBis, menus,  sol, P, costo, pos+1, i+1);
       costo=costo-piatto.costo;
    }
    return;
}
