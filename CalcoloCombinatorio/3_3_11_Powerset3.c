int powerset(int* val, int k, int* sol){
  int count = 0;
  int n;
  printf(":;\n"); //insieme vuoto;
  count++;
  /* wrapper delle chiamate ricorsive*/
  for(n = 1; n <= k; n++){
    count += powerset_r(val, k, sol, n, 0, 0);
  }
  return count;
}

int powerset_r(int* val, int k, int* sol, int n, int pos, int start){
  int count = 0;
  int i;
   /* caso terminale: e' stato raggiunto il numero prefissato di 
      elementi nell'insieme attuale */
  if(pos == n){
    printf(":");
    for(i = 0; i < n; i++){
	printf("%d ", sol[i]);
    }
    printf(";\n");
    return 1;
  }
  /* per tutti gli elementi da start in poi */
  for(i = start; i < k; i++){
    sol[pos] = val[i];
    count += powerset_r(val, k, sol, n, pos+1, i+1);
  }
  return count;
}
