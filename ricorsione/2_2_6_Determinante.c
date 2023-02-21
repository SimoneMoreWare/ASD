int det2x2 (int m[MAX][MAX], int n) {
  return (m[0][0]*m[1][1] - m[0][1]*m[1][0]);
}

int minore (int m[MAX][MAX], int i, int j, int n, int m2[MAX][MAX]) {
  int r, c;
 
  for (r = 0; r < n-1; r++) {
    if (r != i) {
      int rr = r;
      if (r > i) rr--;
      for (c = 0; c < n-1; c++) {
        if (c != j) {
          int cc = c;
          if (c > j) cc--;
          m2[rr][cc] = m[i][j];
        }
      }
    }
  }
}

int determinant(int a[MAX][MAX], int n) {
  int sum, k, i, j, r, c;
  int tmp[MAX][MAX];
  sum = 0;

  if(n == 2)
    return (det2x2(a, n));

  for(k = 0; k < n; k++) {
    minore(a, 0, k, n, tmp);
    sum = sum + a[0][k]*pow(-1,k)*determinant(tmp,n-1);
  }
  return(sum);
}
