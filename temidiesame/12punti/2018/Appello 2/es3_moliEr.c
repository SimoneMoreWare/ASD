#include <stdio.h>
#include <stdlib.h>

void wrapper(int n,int lun,int k,int navi[7]);
void algoritmodiEr(int n_lati_moli,int pos,int m,int *sol,int navi[7],int lun, int k,int *res,int *bestsol);
int check(int n_lati_moli,int k,int m,int *sol,int navi[7],int lun);
int main(){
    int n=4;
    int lun=10;
    int k=7;
    int navi[] = {8,3,5,2,5,2,9};

    wrapper(n,lun,k,navi);

    return 0;
}

void wrapper(int n,int lun,int k,int navi[7]){
    int res=k+1;
    int n_lati_moli = 2*n;

    int m=0; // m blocchi
    int pos=0;
    int i,j;

    int *sol = (int *) malloc(k*sizeof(int));
    int *bestsol = (int *) malloc(k*sizeof(int)); 

    algoritmodiEr(n_lati_moli,pos,m,sol,navi,lun,k,&res,bestsol);

    if(res!=(k+1)){
        printf("Numero minimo di moli: %d ",res/2+res%2);
        for(i=0;i<res;i++){
            printf("{");
            for(j=0;j<k;j++) {
                if (bestsol[j] == i) {
                    printf("%d->%d ", j, navi[j]);
                }
            }
            printf("}");
        }
    }
    if(res==(k+1)) printf("Non è possibile fare nulla");

    free(sol);
    free(bestsol);
}

void algoritmodiEr(int n_lati_moli,int pos,int m,int *sol,int navi[7],int lun, int k,int *res,int *bestsol){

    int i,j;

    if(m>n_lati_moli) return; // se il numero di blocchi da utilizzare è maggiore dei lati delle moli non ha senso continuare

    if(pos>=k){  //condizione di terminazione
        if(check(n_lati_moli,k,m,sol,navi,lun)){//vedo se con queste partizioni posso riempire adeguatamente le moli , ovviamente non sforo con la lunghezza
            if(m<(*res)){ //le navi che ho disposto in m blocchi migliora il risultato finora migliore? 
                (*res)=m;
                for(j=0;j<k;j++){
                    bestsol[j]=sol[j]; //memorizzo vettore sol
                    }
                }
            }
        return;
    }

    
    for(i=0;i<m;i++){
        sol[pos]=i;
        algoritmodiEr(n_lati_moli,pos+1,m,sol,navi,lun,k,res,bestsol);
    }

    sol[pos] = m;
    algoritmodiEr(n_lati_moli,pos+1,m+1,sol,navi,lun,k,res,bestsol);

}

int check(int n_lati_moli,int k,int m,int *sol,int navi[7],int lun){

    int i,j;
    //printf("partizione in %d blocchi: ", m);
    int sommalunghezze;
    if(m>n_lati_moli) return 0;

    for(i=0;i<m;i++){
       // printf("{ ");
        sommalunghezze=0;
        for(j=0;j<k;j++){
            if(sol[j]==i){
                //printf("%d->%d ", j,navi[j]); //allora posso stampare
                sommalunghezze=sommalunghezze+navi[j];
            }
            if(sommalunghezze>lun) return 0;
        }
       // printf("}  ");

    }
   // printf("\n");

    return 1; //significa che tutte le navi rietrano nelle moli
}
