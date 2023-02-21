#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int Ogg_prezzo,Ogg_lun;
}Ogg_nastro;

int f_controllo(int pos,int len_max,Ogg_nastro *sol){
    int i,ret;
    int len_tmp=0;
    
    for(i=0;i<pos;i++){
        len_tmp+=sol[i].Ogg_lun;
    }
    
    if(len_tmp<=len_max){
        ret=1;
    }else{
      ret=0;
    }
    
    return ret;
}

int f_val_max(Ogg_nastro *sol,int pos){
    int i,sol_val=0;
    
    for(i=0;i<pos;i++){
        sol_val+=sol[i].Ogg_prezzo;
    }
    
    return sol_val;
}

void disp_rip(int pos,int n,int k,int len_max,Ogg_nastro *val,Ogg_nastro *sol,Ogg_nastro *best_sol,int *best_val,int *dim_best_sol){
int j,i,controllo,sol_val;
    
if(pos>=k){
    controllo=f_controllo(pos,len_max,sol);
    sol_val=f_val_max(sol,pos);
    
    if(controllo==1 && sol_val>*best_val){
        *best_val=sol_val;
        *dim_best_sol=pos;
        for(j=0;j<pos;j++){
            best_sol[j].Ogg_lun=sol[j].Ogg_lun;
            best_sol[j].Ogg_prezzo=sol[j].Ogg_prezzo;
        }
    }
    return;
}
for(i=0;i<n;i++){
    sol[pos].Ogg_lun=val[i].Ogg_lun;
    sol[pos].Ogg_prezzo=val[i].Ogg_prezzo;
    disp_rip(pos+1,n,k,len_max,val,sol,best_sol,best_val,dim_best_sol);
}
    
return;
}

void wrapper(int k,int n,Ogg_nastro *val){
    Ogg_nastro *sol=calloc(k,sizeof(Ogg_nastro));
    Ogg_nastro *best_sol=calloc(k,sizeof(Ogg_nastro));
    int i,best_val=0;
    int dim_best_sol=0;
    
    for(i=1;i<k;i++){
        disp_rip(0,n,i,4,val,sol,best_sol,&best_val,&dim_best_sol);
    }
    for(i=0;i<dim_best_sol;i++){
        printf("lunghezza->%d , prezzo->%d\n",best_sol[i].Ogg_lun,best_sol[i].Ogg_prezzo);
    }
    printf("\n");

    printf("best_val->%d\n",best_val);
    free(best_sol);
    free(sol);
}

int main(){
    Ogg_nastro v_in[4];
    v_in[0].Ogg_lun=1;v_in[0].Ogg_prezzo=1;
    v_in[1].Ogg_lun=2;v_in[1].Ogg_prezzo=5;
    v_in[2].Ogg_lun=3;v_in[2].Ogg_prezzo=8;
    v_in[3].Ogg_lun=4;v_in[3].Ogg_prezzo=9;
    wrapper(4,4,v_in);
    
    return 0;
}

