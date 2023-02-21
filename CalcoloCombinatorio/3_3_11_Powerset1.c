int powerset(int pos, int *val, int *sol, int k, 
             int start, int count) {
  int i;

  /* caso terminale: non ci sono piu' elementi */
  if (start >= k) {
    for (i = 0; i < pos; i++)
      printf("%d ", sol[i]);
    printf("\n");
    return count+1;
  }


  /* per tutti gli elementi da start in poi */
  for (i = start; i < k; i++) {
    /* includi l'elemento e ricorri */
    sol[pos] = val[i];
    count = powerset(pos+1, val, sol, k, i+1, count);
  }
  /* non aggiungere nulla e ricorri */
  count = powerset(pos, val, sol, k, k, count);

  return count;
}
