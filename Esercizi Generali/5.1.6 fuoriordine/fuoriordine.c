#include <stdlib.h>
#include <stdio.h>

int fuoriOrdine(int *, int);
int fuoriOrdineR(int *A, int *B, int l, int r);
int fondi(int *, int *, int, int, int);

int main(int argc, char **argv) {

    int n = 0, i, *v;


    if (argc < 2) {
        fprintf(stderr, "Usage: invCount <elements_count>\n");
        exit(-1);
    }

    n = atoi(argv[1]);

    if (n<=0) {
        fprintf(stderr, "Invalid number of elements provided\n");
        exit(-1);
    }

    v = (int*) malloc (n * sizeof(int));
    if (v == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(-1);
    }

    fprintf(stdout, "Please type the %d element(s) required to fill the array\n", n);
    for(i=0;i<n;i++) {
        fprintf(stdout, "Element %d of %d > ", i+1, n);
        fscanf(stdin, "%d", &v[i]);
        if (v[i] < 0 || v[i] >= n) {
            fprintf(stderr, "Invalid element\n");
            free(v);
            exit(-1);
        }
    }

    fprintf(stdout, "%d inversions in given array\n", fuoriOrdine(v, n));
    free(v);

    return 0;
}

int fuoriOrdine(int *A, int n) {
  int l=0, r=n-1, count, *B;
  B = calloc(n, sizeof(int));
  count = fuoriOrdineR(A, B, l, r);
  free(B);
  return count;
}

int fuoriOrdineR(int *A, int *B, int l, int r) {
  int count, q;

  if (r<=l)
    return 0;

  q = (l+r)/2;

  count = fuoriOrdineR(A, B, l, q);
  count += fuoriOrdineR(A, B, q+1, r);
  count += fondi(A, B, l, q, r);
  return count;
}


int fondi(int *A, int *B, int l, int q, int r) {
  int i = l, j = q+1, k, count = 0;

  for (k = l; k <= r; k++)
    if (i > q)
      B[k] = A[j++];
    else if (j > r)
      B[k] = A[i++];
    else if (A[i] < A[j])
      B[k] = A[i++];
    else {
      B[k] = A[j++];
      count += (q-i+1);
    }
  for ( k = l; k <= r; k++ )
    A[k] = B[k];
  return count;
}
