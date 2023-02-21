#include <stdio.h>
#include <stdlib.h>

void ruota(int *vett, int d, int N);

int main()
{
    int vett[10] = {5,4,10,-1,7,20,11,-3,6,34}, N = 10, d = 5,i;

    printf("Vettore originario:\n");

    for(i=0; i<N; i++)
        printf("%d ", vett[i]);
    printf("\n");

    ruota(vett, 3, 10);

    printf("Vettore ruotato di %d posizioni:\n", d);

    for(i=0; i<N; i++)
        printf("%d ", vett[i]);

    return 0;
}

void ruota(int *vett, int d, int N){
    int i, tmp[N];

    if(d > 0){
        for(i=0; i<N; i++)
            tmp[(i+d)%N] = vett[i];
    } else if (d < 0){
        for(i=0; i<N; i++)
            //la somma per d in realtà sarebbe una sottrazione poichè d è negativo
            tmp[(i+N+d)%N] = vett[i];
    }

    //ricopio nel vettore originario
    for(i=0; i<N; i++)
        vett[i]=tmp[i];

    return;
}
