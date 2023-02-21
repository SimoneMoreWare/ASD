void SP_rec(int n, int m, int pos, int *sol, int *val) {
  int i, j;
  if (pos >= n) {
    printf("partizione in %d blocchi: ", m);
    for (i = 0; i < m; i++) 
      for (j = 0; j < n; j++) 
        if (sol[j] == i) printf("%d ", val[j]);
    printf("\n");
    return;
  }
  for (i = 0; i < m; i++) {
    sol[pos] = i;
    SP_rec(n, m, pos+1, sol, val);
  }
  sol[pos] = m;
  SP_rec(n, m+1, pos+1, sol, val);
}
