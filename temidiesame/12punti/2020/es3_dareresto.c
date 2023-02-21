#include <stdio.h>
#include <stdlib.h>
void wrapper(int r,int n,int val[3],int disp[3]);
void disp_sempl(int pos,int *sol,int val[3],int disp[3],int n,int r,int dim_tot,int k,int *stop);
int main(){
    int n=3;
    int val[]={1,10,25};
    int disp[]={10,3,2};
    int r=30;
    wrapper(r,n,val,disp);
    return 0;
}

void wrapper(int r,int n,int val[3],int disp[3]){

    int dim_tot=0;
    int i;
    for(i=0;i<n;i++) dim_tot=dim_tot+disp[i];

    int *sol = (int *) malloc(dim_tot*sizeof(int));
    int pos=0;
    int stop=0;
    for(i=1;i<=dim_tot && stop==0;i++) disp_sempl(pos,sol,val,disp,n,r,dim_tot,i,&stop);
    if(stop==0) printf("Soluzione non trovata");
    free(sol);
}

void disp_sempl(int pos,int *sol,int val[3],int disp[3],int n,int r,int dim_tot,int k,int *stop){
    int i;
    int resto_attuale;
    if((*stop)==1) return;
    if(pos>=k){
        resto_attuale=0;
        for(i=0;i<k;i++) resto_attuale=resto_attuale+sol[i];
        if(resto_attuale==r){
            printf("Numero minimo di monete %d\n",k);
            for(i=0;i<k;i++) printf("%d ",sol[i]);
            (*stop)=1;
        }
        return;
    }

    for(i=0;i<n;i++){
        if(disp[i]>0){
            disp[i]--;
            sol[pos]=val[i];
            disp_sempl(pos+1,sol,val,disp,n,r,dim_tot,k,stop);
            disp[i]++;
        }
    }
}
