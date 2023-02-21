/*   main.c
 *   @author  : Gabriele Iurlaro
 *   @  site  : http://iurlaro.com
 *   @Modified: 22/12/2020, 19:43:49
*/
#include <stdio.h>
#include <stdlib.h>

#include "st.h"

typedef struct{
    int *occ;
    float r;
}hotel_t;

ST readPrenotazioni(FILE *in){
    ST tmp;
    int ar, per;
    char id[21];
    tmp = STinit(32);
    while(fscanf(in, "%s %d %d\n", id, &ar, &per) == 3){
        STinsert(tmp, itemCreate(id,ar,per));
    }
    return tmp;
}

void fillSol(FILE *in, int *sol, int P, ST t){
    int i,h, j;
    char id[21];
    for(i=0; i<P; i++){
        fscanf(in, "%s %d", id, &h);
        j = STsearchbyname(t, id);
        sol[j] = h;
    }
}

void riempiHotel(hotel_t hotel, prenotazione t){
    int i, arr, per;
    arr = t.arrivo;
    per = t.pernottamenti;
    for(i=arr; i<arr+per; i++){
        hotel.occ[i]++;
    }
}

float calcolaRiempimentoMedio(hotel_t hotel, int M, int X){
    float r;
    int sum=0,i;
    for(i=0; i<X; i++)
        sum += hotel.occ[i];
    r = (float)(sum/(M*X));
    return r;
}

void getMinMax(hotel_t *hotel, int N, float *min, float *max){
    int i;
    for(i=0; i<N; i++){
        if(hotel[i].r > *max || *max == -1)
            *max = hotel[i].r;
        if(hotel[i].r < *min || *min == -1)
            *min = hotel[i].r;
    }
}
float f(hotel_t *hotel, int N,int a, int b){
    float sum=0, min = -1, max = -1,k;
    int i;
    getMinMax(hotel, N, &min, &max);
    k = (max-min)/max;
    for(i=0; i<N; i++){
        sum += k*(hotel[i].r-b);
    }
    return a*sum;
}
int check(ST table, hotel_t *hotel, int *M, int *sol, int P, int N, int X){
    int i,j;
    prenotazione t;
    for(i=0; i<P; i++){
        t = STgetbyindex(table, i);
        riempiHotel(hotel[sol[i]], t);
    }
    for(i=0; i<N; i++){
        for(j=0; j<X; j++){
            if(hotel[i].occ[j] > M[i])
                return 0;
        }
    }
    return 1;
}

void resetHotel(hotel_t *hotel, int N, int X){
    int i, j;
    for(i=0; i<N; i++)
        for(j=0; j<X; j++)
           hotel[i].occ[j] = 0;
}

void algoritmoER(hotel_t *hotel,int *M, int pos, int *sol, int *bestsol, float *bestV, ST t,int m, int N, int X, int P, int a, int b){
    int i,j;
    float tmpval;
    if(pos >= P){
        if(check(t, hotel, M, sol, P, N, X)){
            tmpval = f(hotel, N, a, b);
            if(tmpval > *bestV){
                *bestV = tmpval;
                for(i=0; i<P; i++)
                    bestsol[i] = sol[i];
            }
        }
        resetHotel(hotel, N, X);
       return;
    }
    for(i=0; i<m; i++){
        sol[pos] = i;
        algoritmoER(hotel,M, pos+1, sol, bestsol, bestV, t, m, N, X, P, a, b);
    }
    sol[pos] = N;
    algoritmoER(hotel, M,  pos+1, sol, bestsol, bestV, t,m+1, N, X, P, a, b);
}

void generaSoluzione(int *sol,int *M, hotel_t *hotel, ST t, int N, int X, int P, int a, int b){
    int *bestsol,i;
    float bestV = 0;
    bestsol = malloc(P* sizeof(int));
    algoritmoER(hotel, M, 0, sol, bestsol, &bestV, t, 0, N, X, P, a, b);
    for(i=0; i<P; i++)
        sol[i] = bestsol[i];
    free(bestsol);
}

int main(int argc, char **argv){
    FILE *in, *out;
    int N, X, a, b, *M, i, P, *sol;
    char id[21];
    hotel_t *hotel;
    ST prenotazioni;
    printf("Inserisci N, X, a, b:\n>");
    scanf("%d %d %d %d",&N, &X, &a, &b);
    hotel = malloc(N* sizeof(hotel_t));
    for(i=0; i<N; i++){
        hotel[i].occ = calloc(X,sizeof(int));
    }
    M = malloc(N* sizeof(int));
    for(i=0; i<N; i++)
        scanf("%d", &M[i]);
    in = fopen(argv[1], "r");
    prenotazioni = readPrenotazioni(in);
    fclose(in);
    P = getN(prenotazioni);
    sol = malloc(P* sizeof(int));
    in = fopen(argv[2], "r");
    fillSol(in, sol, P, prenotazioni);
    fclose(in);
    if(check(prenotazioni, hotel, M, sol, P, N, X))
        printf("Soluzione in input valida.\n");
    else
        printf("Soluzione in input non valida.\n");
    generaSoluzione(sol, M, hotel, prenotazioni, N, X, P, a, b);
    out = fopen(argv[3], "w");
    for(i=0; i<P; i++){
        fprintf(out, "%s %d\n", STgetbyindex(prenotazioni, i).id, sol[i]);
    }
    fclose(out);
}