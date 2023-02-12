/*
 * Data una funzione con un vettore e la sua dimensione, creare un nuovo vettore in cui ciascun elemento è la media tra
 * l'elemento corrispondente del vettore di partenza, quello precedente e quello dopo
 * (i casi estremi vanno gestiti come buffer circolare, però);
 */

#include <stdio.h>
#include <stdlib.h>
float* f(int val[9],int n);
int main(){
    int val[]={1,2,3,4,5,6,7,8,9};
    int n=9;
    int i;
    float *res;
    res=f(val,n);
    for(i=0;i<n;i++) printf("%f ",res[i]);
    free(res);
    return 0;
}

float* f(int val[9],int n){
    float *res=(float *) malloc(n*sizeof(float));
    int first=val[0];
    int last=val[n-1];
    int i;
    for(i=0;i<n;i++){
        if(i==0) res[i] = (float) (last+val[i]+val[i+1])/3;
        else if(i==n-1) res[i] = (float) (val[i-1]+val[i]+first)/3;
        else res[i]=(float) (val[i-1]+val[i]+val[i+1])/3;
    }
    return res;
}
