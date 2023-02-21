void SP_rec(int n, int k, int m, int pos, int *sol, int *val) {
  int i, j;
  if (pos >= n) {
    if (m == k) {
      printf("partizione: ");
      for (i = 0; i < m; i++) {
        printf("{ ");
        for (j = 0; j < n; j++) {
          if (sol[j] == i) printf("%d ", val[j]);
        }
        printf("}  ");
     }
      printf("\n");
    }
    return;
  }
  for (i = 0; i < m; i++) {
    sol[pos] = i;
    SP_rec(n, k, m, pos+1, sol, val);
  }
  sol[pos] = m;
  SP_rec(n, k, m+1, pos+1, sol, val);
}
