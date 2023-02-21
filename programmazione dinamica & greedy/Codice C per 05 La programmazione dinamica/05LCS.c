/* OPTIMIZED VERSION WITHOUT MATRIX B. VERSION WITH MATRIX B WITHIN COMMENTS */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 101

int subseq(char *X, char *Y);
int LCSlength(char *X, char *Y);
int LCSlengthDP(char *X, char *Y);
void displaySol(char *X, char *Y, int **b);


int main() {
  char X[MAXL], Y[MAXL];
  printf("Input X: ");
  scanf("%s", X);
  printf("Input Y: ");
  scanf("%s", Y);
  if (subseq(X,Y))
    printf("X is a subsequence of Y\n");
  else
    printf("X is not a subsequence of Y\n");

  printf("Recursive approach: LCS has length %d\n", LCSlength(X, Y));
  printf("Dynamic Programming approach:\n");
  printf("LCS has length %d\n", LCSlengthDP(X, Y));

  return 0;
}

int subseq(char *X, char *Y) {
  while (*X != '\0') {
    if (*Y == *X) {
      Y++;
      if (*Y == '\0')
        return 1;
    }
    X++;
  }
  return 0;
}

int LCSlengthDP(char *X, char *Y) {
  int i, j, m, n, **c;
/*  int i, j, m, n, **c, **b; */
  m = strlen(X);
  n = strlen(Y);

  c = calloc((m+1), sizeof(int *));
/*  b = calloc((m+1), sizeof(int)); */

  for (i = 0; i <= m; i++) {
    c[i] = calloc((n+1), sizeof(int));
/*    b[i] = calloc((n+1), sizeof(int)); */
  }

  for (i=1; i<=m; i++)
    for (j=1; j <=n; j++)
      if (X[i-1]==Y[j-1]) {
        c[i][j] = c[i-1][j-1]+1;
/*        b[i][j] = 1; */
      }
      else {
        if (c[i-1][j] >= c[i][j-1]) {
          c[i][j] = c[i-1][j];
/*          b[i][j] = 2; */
        }
        else {
          c[i][j] = c[i][j-1];
/*          b[i][j] = 3; */
        }
      }

  printf("c is: \n");
  for (i=0; i<=m; i++) {
    for (j=0; j <=n; j++)
      printf("%d ", c[i][j]);
    printf("\n");
  }
/*
  printf("b is: \n");
  for (i=0; i<=m; i++) {
    for (j=0; j <=n; j++)
      printf("%d ", b[i][j]);
    printf("\n");
  }
*/

  printf("LCS is: ");
/*   displaySol(X, Y, b); */
  displaySol(X, Y, c);
  printf("\n");
  return c[m][n];
}

void displaySolR(char *X, char *Y, int **c, int i, int j) {
  if ((i==0) || (j==0)) {
    return;
  }
  if (X[i-1]==Y[j-1]) {
    displaySolR(X, Y, c, i-1, j-1);
    printf("%c", X[i-1]);
    return;
  }
  if (c[i-1][j] >= c[i][j-1])
    displaySolR(X, Y, c, i-1, j);
  else
    displaySolR(X, Y, c, i, j-1);
}

void displaySol(char *X, char *Y, int **c) {
  int m, n;
  m = strlen(X);
  n = strlen(Y);
  displaySolR(X, Y, c, m, n);
}

/*
void displaySolR(char *X, char *Y, int **b, int i, int j) {
  if ((i==0) || (j==0)) {
    return;
  }
  if (b[i][j]==1) {
    displaySolR(X, Y, b, i-1, j-1);
    printf("%c", X[i-1]);
    return;
  }
  if (b[i][j]==2)
    displaySolR(X, Y, b, i-1, j);
  else
    displaySolR(X, Y, b, i, j-1);
}

void displaySol(char *X, char *Y, int **b) {
  int m, n;
  m = strlen(X);
  n = strlen(Y);
  displaySolR(X, Y, b, m, n);
}
*/

int max(int a, int b) {
  if (a >= b)
    return a;
  return b;
}

int lengthR(char *X, char *Y, int i, int j) {
  if ( (i == 0) || (j == 0))
    return 0;
  if (X[i] == Y[j])
    return 1 + lengthR(X, Y, i-1, j-1);
  else
    return max(lengthR(X, Y, i-1, j), lengthR(X, Y, i, j-1));
}

int LCSlength(char *X, char *Y) {
  return lengthR(X, Y, strlen(X), strlen(Y));
}

