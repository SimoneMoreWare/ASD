#include <stdio.h>
#include <stdlib.h>

typedef struct{
int dx,sx;
}interv;

int f_SOL_COMPATIBILE(interv *sol,int pos){
int i,ret=1;
for(i=0;i<pos;i++){
    if(sol[i].sx==sol[i+1].sx || sol[i].dx==sol[i+1].dx || sol[i].dx>sol[i+1].sx){
        ret=0;
        }
    }
return ret;
}

int f_SOL_MAX(interv *sol,interv *best_sol,int *somma_max_Mia,int pos){
int j,i,ret=0;
int somma_tmp=0;
for(i=0;i<pos;i++){
    somma_tmp+=(sol[i].dx-sol[i].sx);
    }
j=pos-1;
if(somma_tmp>*somma_max_Mia){
    *somma_max_Mia=somma_tmp;
    ret=1;
    }
    /*Se non metto questa (else if) ottengo (1,2)(2,5)(5,7) la cui somma
    delle durate è 6,quindi è giusto. Se voglio (1,2)(2,5)(6,8) mi serve
    anche questo (else if).*/
    else if(somma_tmp==*somma_max_Mia){
    if(best_sol[j].dx<sol[j].dx){
        ret=1;
        }
    }
return ret;
}

int powerset(int pos,int start,int *dim_best,int *somma_max_Mia,interv *val,interv *sol,interv *best_sol,int n,int k){
int i,j,n_sol=0;
if(pos==n){
    if(f_SOL_COMPATIBILE(sol,pos)==1 && f_SOL_MAX(sol,best_sol,somma_max_Mia,pos)==1){
        for(j=0;j<pos;j++){
        best_sol[j].dx=sol[j].dx;
        best_sol[j].sx=sol[j].sx;
        }
        *dim_best=pos;
        return 1;
        }
    return 0;
    }
for(i=start;i<k;i++){
    sol[pos].dx=val[i].dx;
    sol[pos].sx=val[i].sx;
    n_sol+=powerset(pos+1,i+1,dim_best,somma_max_Mia,val,sol,best_sol,n,k);
    }
return n_sol;
}

void intervSel(int N,interv *v){
int i,x,n_sol=0;
int somma_max=0;
int dim_best=0;
interv *sol=malloc(N*sizeof(interv));
interv *best_sol=malloc(N*sizeof(interv));
for(x=1;x<=N;x++){
    n_sol=powerset(0,0,&dim_best,&somma_max,v,sol,best_sol,x,N);
    }
printf("SOLUZIONE_MIGLIORE\n");
for(i=0;i<dim_best;i++){
    printf("%d %d\n",best_sol[i].sx,best_sol[i].dx);
}printf("\n");
free(best_sol);
free(sol);
return;
}

int main(){
    interv v_in[6];
    v_in[0].sx=1;v_in[0].dx=2;
    v_in[1].sx=2;v_in[1].dx=4;
    v_in[2].sx=2;v_in[2].dx=5;
    v_in[3].sx=3;v_in[3].dx=5;
    v_in[4].sx=5;v_in[4].dx=7;
    v_in[5].sx=6;v_in[5].dx=8;
    intervSel(6,v_in);
return 0;
}
