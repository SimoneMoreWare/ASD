#include <stdio.h>
#include <stdlib.h>
//disposizioni ripetute in quanto l'ordina conta

void disposizoioni_ripetute(int pos, char *val,char *sol, int n, int k);
int check(char *sol, int k);

int main(){
    char val[]={'A','E','I','O','U'};
    int n=5;
    int k=6;
    char *sol;
    sol=(char *) malloc(k*sizeof(char));
    disposizoioni_ripetute(0,val,sol,n,k);
    return 0;
}

void disposizoioni_ripetute(int pos, char *val,char *sol, int n, int k){
    int i;
    if(pos>=k){
        if(check(sol,k)==1){
            for(i=0;i<k;i++) printf("%c ",sol[i]);
            printf("\n");
        }
        return;
    }
    for(i=0;i<n;i++){
        sol[pos]=val[i];
        disposizoioni_ripetute(pos+1,val,sol,n,k);
    }
}

int check(char *sol, int k){
    if(k<5) return 0;
    int tmp[]={0,0,0,0,0};
    for(int i=0;i<k;i++){
        switch (sol[i]) {
            case 'A':
                tmp[0]++;
                break;
            case 'E':
                tmp[1]++;
                break;
            case 'I':
                tmp[2]++;
                break;
            case 'O':
                tmp[3]++;
                break;
            case 'U':
                tmp[4]++;
                break;
            default:
                break;
        }
    }
    for(int i=0;i<5;i++) if(tmp[i]==0) return 0;

    return 1;
}
