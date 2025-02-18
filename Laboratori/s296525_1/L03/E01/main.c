#include <stdio.h>

int mergeHalves(int* a, int l, int r, int majL, int majR, int countL, int countR, int* count) {
    if (majL == majR) {
        *count = countL + countR; 
        return majL;
    }
    
    int i,
        h = r-l,
        m = l+h/2;
    if (majL != -1) {
        for(i = m+1; i < r; i++) {
            if(a[i] == majL) {
                countL++;
            }
        }
        if(countL > h/2) {
            *count = countL;
            return majL;
        }
    }

    if (majR != -1) {
        for(i = l; i < m; i++) {
            if(a[i] == majR) {
                countR++;
            }
        }
        if(countR > h/2) {
            *count = countR;
            return majR;
        }
    }

    return -1;
}

int majorityHalf(int *a, int l, int r, int* count) {
    if(l == r) {
        *count = 1;
        return a[l];
    }

    int h = r-l,
        m = l+h/2,
        majL, countL,
        majR, countR;

    majL = majorityHalf(a, l, m, &countL);
    majR = majorityHalf(a, m+1, r, &countR);
    
    return mergeHalves(a, l, r, majL, majR, countL, countR, count);
}

int majority(int *a, int N) {
    int majL, majR, countL = 0, countR = 0;
    majL = majorityHalf(a, 0, N/2, &countL);
    majR = majorityHalf(a, N/2+1, N, &countR);

   return mergeHalves(a, 0, N, majL, majR, countL, countR, &countL);
}

int main() {
    int N = 7, vet[7] = {3,3,9,4,4,5,3},
        maj;
    maj = majority(vet, N);
    if (maj != -1) {
        printf("Maggioritario: %d", maj);
    } else {
        printf("Non e' stato trovato un valore maggioritario.");
    }
    return 0;
}
