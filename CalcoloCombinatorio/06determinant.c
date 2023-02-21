#include <stdio.h>
#include <math.h>
#define MAX 10

int readDim();
void readMatrix(int m[][MAX], int n);
void writeMatrix(int m[][MAX], int n);
int determinant(int m[][MAX], int n);


int main() {
  int a[MAX][MAX], tmp[MAX][MAX], i, j, n, r, c, k;

  n = readDim();
  readMatrix(a, n);
  printf("determinant(a) = %d\n", determinant(a, n));
  return 0;
}


int readDim() {
  int n;
  do {
    printf("input n:  ");
    scanf("%d", &n);
    if (n < 2)
      printf("n must be >= 2, input again! \n");
  }
  while (n<2);
  return n;
}

void readMatrix(int m[][MAX], int n) {
  int i, j;
  printf("input matrix by rows\n");
  for (i=0; i < n; i++)
    for (j=0; j < n; j++){
      printf("m[%d][%d] = ", i, j);
      scanf("%d", &m[i][j]);
    }
}

int det2x2(int m[][MAX]) {
  return(m[0][0]*m[1][1] - m[0][1]*m[1][0]);
}


void minor(int m[][MAX],int i,int j,int n,int m2[][MAX]){
  int r, c, rr, cc;
  for(r = 0, rr = 0; r < n; r++)
    if (r != i) {
      for(c = 0, cc = 0; c < n; c++)
        if(c != j) {
           m2[rr][cc] = m[r][c];
           cc++;
        }
      rr++;
    }
}


int determinant(int a[][MAX], int n) {
  int sum, k, i, j, r, c;
  int tmp[MAX][MAX];
  sum = 0;

  if (n == 2)
    return (det2x2(a));

  for (k = 0; k < n; k++) {
    minor(a, 0, k, n, tmp);
    sum = sum + a[0][k]*pow(-1,k)*determinant(tmp,n-1);
  }
  return(sum);
}

