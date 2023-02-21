void powerset(int pos, int *val, int *sol,int k) {
  int j;

  /* caso terminale: non ci sono piu' elementi */
  if (pos >= k) {
    printf("{\t");
    for (j = 0; j < k; j++)
      if (sol[j] != 0)
        printf("%d\t", val[j]);
    printf("}\n");
    return;
  }
  
  sol[pos] = 0;
  powerset(pos+1, val, sol, k);
  sol[pos] = 1;
  powerset(pos+1, val, sol, k);
}

