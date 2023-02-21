/*[MANCA_ORDINAMENTO_VETTORE]*/
#include<stdio.h>
#include<stdlib.h>

int *merge_mia(int *v1,int *v2,int *v3,int dim_a,int dim_b,int dim_c);

int main(){
    int a[]={1,5,7,9}, na=4;
    int b[]={3,4,6,10,13}, nb=5;
    int c[]={0,8}, nc=2;
    int *d;

    d = merge_mia(a,b,c,na,nb,nc);

    int i=0;
    printf("VETTORE_FINALE\n:");
    for(i=0;i<na+nb+nc;i++){
        printf("%d ", d[i]);
    }
free(d);
return 0;
}
/*
devo semplicemente creare un vettore e poi inserisco man mano tutti i valori partento dalla posizione 0 dima-1 , dima-dima+dimb-1 e dimb+dima dimb+dima+dimc-1
*/
int *merge_mia(int *v1,int *v2,int *v3,int dim_a,int dim_b,int dim_c){
int *d=malloc((dim_a+dim_b+dim_c)*sizeof(int));
int i;
int pos_a=0;
int pos_b=0;
int pos_c=0;
int i_v1=i;
int i_v2=i+dim_a;
int i_v3=i+dim_a+dim_b;
int x;

for(x=0;x<dim_a+dim_b+dim_c;x++){
    d[x]=0;
}

for(i=0;i<dim_a+dim_b+dim_c;i++){
printf("i->%d\n",i);
if(pos_a<dim_a){
    printf("d[%d]=v1[%d]\n",i_v1,pos_a);
    d[i_v1]=v1[pos_a];
    i_v1++;
    pos_a++;
    }
if(pos_b<dim_b){
    printf("d[%d]=v2[%d]\n",i_v2,pos_b);
    d[i_v2]=v2[pos_b];
    i_v2++;
    pos_b++;
    }
if(pos_c<dim_c){
    printf("d[%d]=v3[%d]\n",i_v3,pos_c);
    d[i_v3]=v3[pos_c];
    i_v3++;
    pos_c++;
    }
printf("VETT_TMP\n");
for(x=0;x<dim_a+dim_b+dim_c;x++){
    printf("%d ",d[x]);
    }printf("\n");
}
return d;
}
