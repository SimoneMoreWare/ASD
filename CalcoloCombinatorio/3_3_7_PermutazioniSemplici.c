int perm_sempl(int pos,int *val,int *sol,int *mark,int n,int count) {
  int i;

  if (pos >= n) {
    for (i = 0; i < n; i++)
      printf("%d ", sol[i]);
    printf("\n");
    return count+1;
  }

  for (i = 0; i < n; i++) {
    if (mark[i] == 0) {
      mark[i] = 1;
      sol[pos] = val[i];
      count = perm_sempl(pos+1, val, sol, mark, n,  count);
      mark[i] = 0;
    }
  }
  return count;
}
