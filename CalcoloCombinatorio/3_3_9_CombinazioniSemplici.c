int comb_sempl(int pos, int *val, int *sol, int n, int k, 
               int start,  int count){
  int i;

  if (pos >= k) {
    for (i=0; i<k; i++)
      printf("%d ", sol[i]);
    printf("\n");
    return count+1;
  }

  for (i=start; i<n; i++) {
    sol[pos] = val[i];
    count = comb_sempl(pos+1, val, sol, n, k, i+1, count);
  }
  return count;
}
