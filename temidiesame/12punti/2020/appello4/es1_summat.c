#include <stdio.h>
#include <stdlib.h>
void mySum(int A[3][3], int nA, int B[2][2], int nB, char *scelta_A, char *scelta_B);

int main(){
    int A[3][3] = {
            {1,2,3},
            {3,2,-3},
            {11,12,-6}
    };
    int B[2][2] = {
            {2,0},
            {7,1}
    };
    int nA=3;
    int nB=2;
    char scelta_A[3];
    char scelta_B[3];
    mySum(A,nA,B,nB,scelta_A,scelta_B);
    printf("%s %s",scelta_A,scelta_B);
    return 0;
}

int abs(int a){
    if(a<0) return (-1)*a;
    return a;
}

void mySum(int A[3][3], int nA, int B[2][2], int nB, char *scelta_A, char *scelta_B){
    int minimo=INT_MAX;
    int riga,colonna,i,j;
    int k,t;
    int somma;
    for(riga=0;riga<2;riga++){
        for(colonna=0;colonna<2;colonna++){
            for(i=0;i<nA;i++){
                for(j=0;j<nB;j++){
                    somma=0;
                    if(riga%2==0 && colonna%2==0){
                        //printf("(Riga%dA,Riga%dB)",i,j);
                        for(t=0;t<nA;t++) somma=somma+A[i][t];
                        for(k=0;k<nB;k++) somma=somma+B[j][k];
                        if(abs(somma)<minimo){
                            minimo=somma;
                            scelta_A[0]='R';
                            scelta_A[1]=(char)(i+'0');
                            scelta_B[0]='R';
                            scelta_B[1]=(char)(j+'0');
                        }
                    }
                    if(riga%2==0 && colonna%2!=0){
                        //printf("(Riga%dA,Col%dB)",i,j);
                        for(t=0;t<nA;t++) somma=somma+A[i][t];
                        for(k=0;k<nB;k++) somma=somma+B[k][j];
                        if(abs(somma)<minimo){
                            minimo=somma;
                            scelta_A[0]='R';
                            scelta_A[1]=(char)(i+'0');
                            scelta_B[0]='C';
                            scelta_B[1]=(char)(j+'0');
                        }
                    }
                    if(riga%2!=0 && colonna%2==0){
                        //printf("(Col%dA,Riga%dB)",i,j);
                        for(t=0;t<nA;t++) somma=somma+A[t][i];
                        for(k=0;k<nB;k++) somma=somma+B[j][k];
                        if(abs(somma)<minimo){
                            minimo=somma;
                            scelta_A[0]='C';
                            scelta_A[1]=(char)(i+'0');
                            scelta_B[0]='R';
                            scelta_B[1]=(char)(j+'0');
                        }
                    }
                    if(riga%2!=0 && colonna%2!=0){
                        //printf("(Col%dA,Col%dB)",i,j);
                        for(t=0;t<nA;t++) somma=somma+A[t][i];
                        for(k=0;k<nB;k++) somma=somma+B[k][j];
                        if(abs(somma)<minimo){
                            minimo=somma;
                            scelta_A[0]='C';
                            scelta_A[1]=(char)(i+'0');
                            scelta_B[0]='C';
                            scelta_B[1]=(char)(j+'0');
                        }
                    }
                }
            }
            //printf("\n");
        }
    }
}
