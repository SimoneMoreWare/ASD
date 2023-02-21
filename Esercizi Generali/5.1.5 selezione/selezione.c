#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Item.h"
#define DBG 0

void Swap( Item *v, int n1, int n2);
int partition (Item *A, int l, int r);
int Select(Item *A, int l, int r, int k);

int main(int argc, char *argv[])
{
	int i=0, k, N, sw;
	Item *a;

    if (argc !=3)
    {
        printf("Error in command line, correct format: \n");
        printf("client <number of keys> <1 for random input, 0 for for input from keyboard\n");
        exit(1);
    }
    N = atoi(argv[1]);
    sw = atoi(argv[2]);
	a = (Item *)malloc(N*sizeof(Item));
    if (a == NULL) {
        printf("Memory allocation error\n");
        return EXIT_FAILURE;
    }

	if (sw)
	{
        printf("Filling in the array with random values\n");
        srand(time(NULL));
        for (i = 0; i < N; i++)
            a[i] = ITEMrand();
    }
    else
    {
        printf("Input array values (key is >=0) \n");
        for (i = 0; i < N; i++)
            a[i] = ITEMscan();
        printf("\n");
    }


    printf("The original array is\n");
    for (i = 0; i <N; i++)
    {
        printf("a[%d]: ", i);
        ITEMshow(a[i]);
    }
    printf("\n");

    printf("Input rank in range 0 .. %d \n", N-1);
    scanf("%d", &k);

    i = Select(a, 0, N-1, k);

    printf("Element in a whose rank is %d is: ", k);
    ITEMshow(a[i]);
    printf("\n");

    return 0;
}

void Swap( Item *v, int n1, int n2)
{
	Item	temp;

	temp  = v[n1];
	v[n1] = v[n2];
	v[n2] = temp;
	return;
}


int partition (Item *A, int l, int r)
{
    int i, j;
    Item x = A[r];
    i = l-1;
    j = r;
    for ( ; ; )
    {
        while(ITEMlt(A[++i], x));
        while(ITEMgt(A[--j], x))
            if (j == l)
                break;
        if (i >= j)
            break;
        Swap(A, i, j);
    }
    Swap(A, i, r);
#if DBG
    printf("sottovettore SX\n");
    for (k=l; k<i; k++)
      ITEMshow(A[k]);
    printf("\n");
    printf("pivot\n");
    ITEMshow(A[i]);
    printf("sottovettore DX\n");
    for (k=i+1; k<=r; k++)
      ITEMshow(A[k]);
    printf("\n");
#endif
    return i;
}

int Select(Item *A, int l, int r, int k)
{
    int q;
    if (r <= l)
        return r;
    q = partition(A, l, r);

    if (q-l == k)
        return q;

    if (q-l > k)
        return Select(A, l, q-1, k);
    else
        return Select(A, q+1, r, k-q-1);
}


