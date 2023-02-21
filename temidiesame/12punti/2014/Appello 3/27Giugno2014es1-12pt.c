#include <stdio.h>
#include <stdlib.h>

int ricerca(int *vet1, int *vet2, int d1, int d2);

int main()
{
    int d1 = 8, d2 = 3, vet1[8] = {0, 15, 12, 21, 7, 25, 32, 1}, vet2[3] = {21, 7, 25}, index;

    index = ricerca(vet1,vet2,d1,d2);

    if(index == -1){
        printf("Sottovettore non trovato.");
    } else {
        printf("Sottovettore trovato, indice iniziale %d ", index);
    }
    return 0;
}

int ricerca(int *vet1, int *vet2, int d1, int d2){
    int found = 0,i,j;

    if(d2>d1){
        return -1;
    }

    for(i=0; i<d1; i++){
        if(vet1[i]==vet2[0]){
            found = 1;
            for(j=0; j<d2; j++){
                if(vet1[i+j] != vet2[j])
                    found = 0;
            }
            if(found == 1)
                return i;
        }
    }
    return -1;
}
