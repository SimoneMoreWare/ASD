#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int disgiunte(char stringhe[7][8], int n);
void powerset_combsempl(int pos,int start,int *sol,char stringhe[7][8],int n,int k,int *stop);
int check(int *sol,int k,char stringhe[7][8]);

int main(){
    char stringhe[7][8] = {
            "ABGCIEF",
            "BA",
            "CD",
            "FE",
            "GHBD",
            "JKLGHI",
            "FK"
    };

    int n=7;
    int res;
    res=disgiunte(stringhe,n);
    printf("Numero massimo di stringhe mutualmente raggiungibili : %d",res);

    return 0;
}

int disgiunte(char stringhe[7][8], int n){

    int *sol = (int *) malloc(n*sizeof(int));
    int pos=0;
    int i;
    int start=0;
    int stop=0;
    for(i=n;i>=1 && stop==0;i--) powerset_combsempl(pos,start,sol,stringhe,n,i,&stop);

    free(sol);
    return i+1;
}

void powerset_combsempl(int pos,int start,int *sol,char stringhe[7][8],int n,int k,int *stop){

    int i;

    if((*stop)==1) return;

    if(pos>=k){
        if(check(sol,k,stringhe)){
            (*stop)=1;
            for(i=0;i<k;i++) printf("%s ",stringhe[sol[i]]);
            printf("\n");
        }
        return;
    }

    for(i=start;i<n;i++){
        sol[pos]=i;
        powerset_combsempl(pos+1,i+1,sol,stringhe,n,k,stop);
    }
}

int check(int *sol,int k,char stringhe[7][8]){

    int i,j;
    int p,t;
    for(i=0;i<k;i++){
        for(j=i+1;j<k;j++){
            for(t=0;t<strlen(stringhe[sol[i]]);t++){
                for(p=0;p<strlen(stringhe[sol[j]]);p++){
                    if(stringhe[sol[i]][t]==stringhe[sol[j]][p]) return 0;
                }
            }
        }
    }
    return 1;
}
