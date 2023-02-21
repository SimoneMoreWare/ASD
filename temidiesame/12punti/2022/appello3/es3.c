#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void disposizioniripetute(char *minuscole,char *maiuscole, int pos, char *sol, int N, int k,int countminuscole,int p,FILE *fp);
int checkconsecutivi(int p,char *sol,int k);

int main(){

    int N=26;
    char minuscole[26];
    char maiuscole[26];
    for (int i = 0; i < 26; i++) {
        minuscole[i] = (char) ('a' + i);
        maiuscole[i] = (char) ('A' + i);
    }
    int k=4;
    char *sol = (char *) malloc(k*sizeof(char));
    int p=2;
    int pos=0;
    int countminuscole=0;
    FILE *fp= fopen("ot.txt","w");
    disposizioniripetute(minuscole,maiuscole,pos,sol,N,k,countminuscole,p,fp);
    free(sol);
    return 0;
}

void disposizioniripetute(char *minuscole,char *maiuscole, int pos, char *sol, int N, int k,int countminuscole,int p,FILE *fp){

    int i;

    if(pos>=k){
        if(checkconsecutivi(p,sol,k)) fprintf(fp,"%s\n",sol);
        return;
    }

    for(i=0;i<N;i++){
        if(countminuscole<k/2){
            countminuscole++;
            sol[pos]=minuscole[i];
            disposizioniripetute(minuscole,maiuscole,pos+1,sol,N,k,countminuscole,p,fp);
            countminuscole--;
        }
        sol[pos]=maiuscole[i];
        disposizioniripetute(minuscole,maiuscole,pos+1,sol,N,k,countminuscole,p,fp);
    }

}

int checkconsecutivi(int p,char *sol,int k){
    int i;
    int cnt=0;
    char *tmp=(char *) malloc(k*sizeof(char));
    strcpy(tmp,sol);
    for(i=0;i<k;i++) tmp[i]=(char) tolower(tmp[i]);
    for(i=0;i<k-1;i++){
        if(tmp[i] == tmp[i+1]){
            cnt++;
            if(cnt==p){
                free(tmp);
                return 0;
            }
        }else{
            cnt=0;
        }
    }
   free(tmp);
    return 1;
}
