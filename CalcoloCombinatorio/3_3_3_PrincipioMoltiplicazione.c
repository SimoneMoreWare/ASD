int princ_molt(int pos, Livello *val, int *sol, int n, int count) {
  int i;

  if (pos >= n) {
    for (i = 0; i < n; i++)
      printf("%d ", sol[i]);
    printf("\n");
    return count+1;
  }
  for (i = 0; i < val[pos].num_scelte; i++) {
    sol[pos] = val[pos].scelte[i];
    count = princ_molt(pos+1, val, sol, n, count);
  }
  return count;
}

