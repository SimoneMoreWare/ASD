#include <stdio.h>
#include <stdlib.h>


void f(int n,int k,int mat[4][4]);
void combinazionisemplici(int pos,int start,int k,int n,int *val,int *sol,int m[4][4]);
void generacoppie(int pos,int start, int k,int n,int *val,int *solcoppie,int m[4][4],int *cnt_coppie,int *cnt_indivisibili);

int main(){
    int m[4][4]={
            {0,1,0,0},
            {0,0,1,0},
            {1,0,0,1},
            {1,0,1,0}
    };
    int n=4;
    int k=2;

    f(n,k,m);

    return 0;

}

/*
	n elementi distinti
	insieme da 0 a n-1
	Per ogni
coppia di elementi è noto se questi possono essere separati o no


Tale informazione è riportata in una matrice
quadrata di dimensione n x n
*/

void f(int n, int k, int m[4][4]){
    int *sol = (int *) malloc(n*sizeof(int));
    int start = 0;
    int pos = 0;
    int *val = (int *) malloc(n*sizeof(int));
    for(int i=0;i<n;i++) val[i]=i;
    for(int i=k;i<=n;i++) combinazionisemplici(pos,start,i,n,val,sol,m);
}

void combinazionisemplici(int pos,int start,int k,int n,int *val,int *sol,int m[4][4]){
    int i;
    if(pos>=k){
        int *solcoppie = (int *) malloc(2*sizeof(int));
        int cnt_coppie=0;
        int cnt_indivisbili=0;
        generacoppie(0,0,2,k,sol,solcoppie,m,&cnt_coppie,&cnt_indivisbili); //pos=0 start=0 k=2

        if(cnt_indivisbili==cnt_coppie){
            for(i=0;i<k;i++) printf("%d ",sol[i]);
            printf("\n");
        }

        free(solcoppie);
        return;
    }

    for(i=start;i<n;i++){
        sol[pos]=val[i];
        combinazionisemplici(pos+1,i+1,k,n,val,sol,m);
    }
}

void generacoppie(int pos,int start, int k,int n,int *val,int *solcoppie,int m[4][4],int *cnt_coppie,int *cnt_indivisibili){
    int i;
    if(pos>=k){
        (*cnt_coppie)++;
        if(m[solcoppie[0]][solcoppie[1]]==0 && m[solcoppie[1]][solcoppie[0]]==0) (*cnt_indivisibili)++;
        return;
    }

    for(i=start;i<n;i++){
        solcoppie[pos] = val[i];
        generacoppie(pos+1,i+1,k,n,val,solcoppie,m,cnt_coppie,cnt_indivisibili);
    }
}
