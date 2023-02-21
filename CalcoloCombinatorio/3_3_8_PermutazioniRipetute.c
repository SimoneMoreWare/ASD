int perm_rip(int pos, int *dist_val, int *sol, int *mark, int n, 
             int n_dist, int count){
  int i;

  if (pos >= n) {
    for (i = 0; i < n; i++)
      printf("%d ", sol[i]);
    printf("\n");
    return count+1;
  }

  for (i = 0; i < n_dist; i++) {
    if (mark[i] > 0) {
      mark[i]--;
      sol[pos] = dist_val[i];
      count = perm_rip(pos+1, dist_val, sol, mark, n, n_dist, count);
      mark[i]++;
    }
  }
  return count;
}
