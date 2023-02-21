int disp_rip(int pos, int *val, int *sol, int n, int k, int count){
  int i;

  if (pos >= k) {
    for (i = 0; i < k; i++)
      printf("%d ", sol[i]);
    printf("\n");
    return count+1;
  }
  for (i = 0; i < n; i++) {
    sol[pos] = val[i];
    count = disp_ripet(pos+1, val, sol, n, k, count);
  }

  return count;

}
