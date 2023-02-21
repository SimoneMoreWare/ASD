#include <stdio.h>
#include <stdlib.h>
float **f(int M[3][3], int r, int c);
int main(){
    int M[3][3] = {
            {1,2,1},
            {2,0,2},
            {1,2,1}
    };
    int r=3;
    int c=3;
    int i,j;
    float **M1;
    M1 = f(M,r,c);
    for(i=0;i<r;i++) {
        for (j = 0; j < c; j++) {
            printf("%f ", M1[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<r;i++) free(M1[i]);
    free(M1);
    return 0;
}

float **f(int M[3][3], int r, int c) {
    float **M1;
    int i,j;
    M1 = (float**) malloc(r*sizeof(float*));
    for(i=0;i<r;i++) M1[i] = (float*) malloc(c*sizeof(float));
    int somma;
    for(i=0;i<r;i++){
        for(j=0;j<c;j++){
            somma = 0;
            //angolo in alto a sx
            if(i==0 && j==0){
                somma = somma + M[i][j] + M[i][j+1] + M[i+1][j] + M[i+1][j+1];
                M1[i][j] = (float) somma/4;
            }
                //angolo in alto a dx
            else if(i==0 && j==(c-1)){
                somma = somma + M[i][j] + M[i][j-1] + M[i+1][j-1] + M [i+1][j];
                M1[i][j] = (float) somma/4;
            }
                //bordo sup (tranne angoli)
            else if(i==0 && (j!=(c-1) && j!=0)){
                somma = somma + M[i][j] + M[i][j-1] + M[i][j+1] + M[i+1][j-1] + M[i+1][j] + M[i+1][j+1];
                M1[i][j] = (float) somma/6;
            }
            //bordo laterale sx (tranne angoli)
            else if(j==0 && (i!=(r-1) && i!=0)){
                somma = somma + M[i][j] + M[i-1][j] + M[i-1][j+1] + M[i][j+1] + M[i+1][j+1] + M[i+1][j];
                M1[i][j] = (float) somma/6;
            }
            //angolo in basso a sx
            else if(j==0 && i==(r-1)){
                somma = somma + M[i][j] + M[i-1][j] + M[i][j+1] + M[i-1][j+1];
                M1[i][j] = (float) somma/4;
            }
            //angolo in basso a dx
            else if(j==(c-1) && i==(r-1)){
                somma = somma + M[i][j] + M[i][j-1] + M[i-1][j-1] + M[i-1][j];
                M1[i][j] = (float) somma/4;
            }
                //bordo inf
            else if(i==(r-1) && (j!=(c-1) && j!=0)){
                somma = somma + M[i][j-1] + M[i][j] + M[i][j-1] + M[i-1][j-1] + M[i-1][j] + M[i-1][j+1];
                M1[i][j] = (float) somma/6;
            }
                //bordo laterale dx
            else if(j==(c-1) && (i!=0 && i!=(r-1))){
                somma = somma + M[i][j] + M[i-1][j-1] + M[i-1][j] + M[i][j-1] + M[i+1][j-1] + M[i+1][j];
                M1[i][j] = (float) somma/6;
            }
                //posso usare 9 pos
            else{
                somma = somma + M[i][j] + M[i-1][j-1] + M[i-1][j] + M[i-1][j+1] + M[i][j-1] + M[i][j+1] + M[i+1][j-1] + M[i+1][j] + M[i+1][j+1];
                M1[i][j] = (float) somma/9;
            }
        }
    }
    return M1;
}
