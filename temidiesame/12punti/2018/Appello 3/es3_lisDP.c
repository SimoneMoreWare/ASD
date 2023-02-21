#include<stdio.h>

#define N 16

int  max (int a, int b);
int  LIS(int val[]);
int  LISR(int val[], int pos);
void LISDP(int val[]);
void LISprint(int val[], int P[], int i);

int main(void) {

 int val[N] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
/*  int val[N] = {7, 6, 5, 4, 3, 2, 1}; */
/* int val[N] = {11, 14, 13, 7, 8, 15}; */
/* int val[N] = {1, 2, 3, 4, 5}; */
/* int val[N] = {7, 2, 8, 6, 3, 1, 9, 7, 10}; */
/* int val[N] = {7, 4, 6, 3, 8, 9, 2}; */
  //  int val[N] = {2, 4, 3, 5, 1, 7, 6, 9, 8};

/* int val[N] = {6, 3, 5, 2, 7, 8, 1}; */
/*  int val[N] = {1, 2, 3, 4, 5, 6, 7}; */
    printf("The Longest Increasing Sequence has length %d \n", LIS(val));
    LISDP(val);

    return 0;
}

int LIS(int *val) {
    int i, res = 0, tmp;
    for (i=0; i<N; i++) {
        tmp = LISR(val, i);
        if (tmp > res)
            res = tmp;
    }
    return res;
}

int LISR(int *val, int i) {
    int j, ris;
    ris = 1;
    for (j=0; j < i; j++)
        if (val[j] < val[i])
            ris = max(ris, 1 + LISR(val, j));
    return ris;
}

int max (int a, int b){
    if (a >= b)
        return a;
    return b;
}

void LISDP(int *val) {
    int i, j, ris, L[N], P[N], last;
    ris = 1;
    last = 1;
    L[0] = 1;
    P[0] = -1;
    for (i=1; i<N; i++) {
        L[i] = 1;
        P[i] = -1;
        for (j=0; j<i; j++)
            if ((val[j] < val[i]) && (L[i] < 1 + L[j])) {
                L[i] = 1 + L[j];
                P[i] = j;
            }
        if (ris < L[i]) {
            ris = L[i];
            last = i;
        }
    }
    printf("One of the Longest Increasing Sequences is ");
    LISprint(val, P, last);
    printf("\n");
    printf("and its length is %d\n", ris);

    printf("\n L\n");
    for (i=0; i<N; i++)
        printf("%d ", L[i]);
    printf("\n");

    printf("\n P\n");
    for (i=0; i<N; i++)
        printf("%d ", P[i]);
    printf("\n");
}

void LISprint(int *val, int *P, int i) {
    if (P[i]==-1) {
        printf("%d ", val[i]);
        return;
    }
    LISprint(val, P, P[i]);
    printf("%d ", val[i]);
}
