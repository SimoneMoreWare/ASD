#include <stdio.h>
#include <stdlib.h>

int f_check(char *val,char *sol,int pos,int k){
int i,j,ris;
int *v_occorrenze=malloc(k*sizeof(int));

for(i=0;i<k;i++){
v_occorrenze[i]=0;
}

int flag_B;
for(i=0;i<pos;i++){
    flag_B=0;
    for(j=0;j<k && flag_B==0;j++){
        if(sol[i]==val[j] && v_occorrenze[j]==0){
            v_occorrenze[j]=1;
            flag_B=1;
            }
        }
    }

int flag=1;
for(i=0;i<k;i++){
if(v_occorrenze[i]==0){
    flag=0;
    }
}

if(flag==1){
ris=1;
}else{
ris=0;
}

free(v_occorrenze);
return ris;
}

int F_Ricor(int pos,char *val,char *sol,int n,int k,int n_sol){
int i,ris;
if(pos>=n){
    ris=f_check(val,sol,pos,k);
    if(ris==1){
        for(i=0;i<pos;i++){
        printf("%c",sol[i]);
        }printf("\n");
        return n_sol+1;
        }
    return n_sol;
    }
for(i=0;i<k;i++){
    sol[pos]=val[i];
    n_sol=F_Ricor(pos+1,val,sol,n,k,n_sol);
    }
return n_sol;
}

int main()
{
int n,n_sol;
printf("Inserire n>=k:\n");
scanf("%d",&n);
while(n<5){
printf("ERRORE->Inserire n>=5:\n");
scanf("%d",&n);
}
char vocali[5]={"AEIOU"};
char *sol=malloc(n*sizeof(char));
n_sol=F_Ricor(0,vocali,sol,n,5,0);
printf("n_sol->%d\n",n_sol);
free(sol);
return 0;
}
