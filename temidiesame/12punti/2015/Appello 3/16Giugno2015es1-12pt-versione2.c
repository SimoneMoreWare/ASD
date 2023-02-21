#include <stdio.h>
#include <stdlib.h>
#define DIM 3

void molti_mia_v2(int *v1,int *v2,int n,int *v3);

int main()
{
    int j;
    int v1[DIM]={2,2,2};
    int v2[DIM]={6,6,6};
    int v3[2*DIM]={0};
    molti_mia_v2(v1,v2,DIM,v3);
    for(j=0;j<2*DIM;j++){
        printf("%d ",v3[j]);
    }printf("\n");
    return 0;
}

void molti_mia_v2(int *v1,int *v2,int n,int *v3){
int j_v1,j_v2,pos,shift=0;
int ris_somma,somma,riporto,ciclo=0;

for(j_v2=n-1;j_v2>=0;j_v2--){
    printf("\n");
    printf("// CICLO->%d // \n",ciclo);
    pos=((2*n)-1)-shift;
    for(j_v1=n-1;j_v1>=0 && pos>=0;j_v1--){
        riporto=0;

        printf("v1[%d]->%d\n",j_v1,v1[j_v1]);
        printf("v2[%d]->%d\n",j_v2,v2[j_v2]);
        printf("PRE_MOLT->v3[%d]->%d\n",pos,v3[pos]);

        somma=v3[pos]+v1[j_v1]*v2[j_v2];

        ris_somma=somma%10;
        riporto=somma/10;

        printf("riporto->%d\n",riporto);
        v3[pos]=ris_somma;
        printf("DOPO_MOLT->v3[%d]->%d\n",pos,v3[pos]);
        printf("\n");
        pos--;

        v3[pos]=v3[pos]+riporto;
    }
ciclo++;
shift++;
}
return;
}
